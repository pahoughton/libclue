// 1998-11-06 (cc) Paul Houghton <paul4hough@gmail.com>

#include "MesgQueue.hpp"

#include "User.hpp"
#include "UserGroup.hpp"
#include "DateTime.hpp"
#include "FileStat.hpp"
#include "Str.hpp"
#include "Clue.hpp"

#include <iomanip>

#include <sys/msg.h>
#include <errno.h>

namespace clue {

MesgQueue::MesgQueue(
  const char *	    keyFn,
  char		    proj,
  std::ios::openmode    mode,
  bool		    create
  )
  : keyFileName( keyFn ),
    keyProj( proj ),
    key( -1 ),
    queueFlags( 0 ),
    queueId( -1 ),
    errorNum( E_OK ),
    osErrno( 0 )
{
  if( (key = ftok( keyFileName, proj )) < 0 )
    {
      setError( E_FTOK, errno );
      return;
    }

  FileStat  keyFnStat( keyFn );

  if( ! keyFnStat.good() )
    {
      setError( E_KEY_STAT, keyFnStat.getSysError() );
      return;
    }

  // use the key file's permissions
  queueFlags = keyFnStat.getMode() & 0666;

  if( create ) {
    queueFlags |= IPC_CREAT;

  }

  if( (queueId = msgget( key, queueFlags )) < 0 )
    {
      setError( E_MSGGET, errno );
      return;
    }
}

MesgQueue::~MesgQueue( void )
{
}

bool
MesgQueue::send( const Mesg & mesg, size_type size )
{
  if( msgsnd( queueId, (void *)&mesg, size - sizeof( mesg.mesgType ), 0 ) < 0 )
    return( setError( E_SEND, errno ) );
  else
    return( true );
}

bool
MesgQueue::recv( Mesg & mesg, size_type size, long type )
{
  if( msgrcv( queueId, &mesg, size - sizeof( mesg.mesgType ), type, 0 ) < 0 )
    return( setError( E_RECV, errno ) );
  else
    return( true );
}

MesgQueue::size_type
MesgQueue::getNumMesgsInQueue( void )
{
  struct msqid_ds   qData;

  if( msgctl( queueId, IPC_STAT, &qData ) < 0 )
    return( 0 );
  else
    return( qData.msg_qnum );
}

bool
MesgQueue::remove( void )
{
  struct msqid_ds   qData;

  if( msgctl( queueId, IPC_RMID, &qData ) < 0 )
    {
      return( setError( E_REMOVE, errno ) );
    }
  return( true );
}

bool
MesgQueue::clearError( void )
{
  errorNum = E_OK;
  osErrno = 0;
  return( good() );
}

int
MesgQueue::getOsErrno( void ) const
{
  return( osErrno );
}

bool
MesgQueue::interupted( void ) const
{
  return( osErrno == EINTR );
}

bool
MesgQueue::good( void ) const
{
  return( errorNum == E_OK && osErrno == 0 );
}

const char *
MesgQueue::error( void ) const
{
  static Str errStr;

  errStr = "MesgQueue";

  if( good() )
    {
      errStr << ": ok";
    }
  else
    {
      size_t eSize = errStr.size();

      switch( errorNum )
	{
	case E_FTOK:
	  errStr << ": ftok on '" << keyFileName << "' failed - ";
	  break;

	case E_KEY_STAT:
	  errStr << ": key file '" << keyFileName << "' stat failed -";
	  break;

	case E_MSGGET:
	  errStr << ": msgget failed - ";
	  break;

	case E_SEND:
	  errStr << ": msgsnd failed - ";
	  break;

	case E_RECV:
	  errStr << ": msgrcv failed - ";
	  break;

	case E_REMOVE:
	  errStr << ": remove failed - ";
	  break;

	default:
	  break;
	}

      if( osErrno )
	errStr << strerror( osErrno );

      if( eSize == errStr.size() )
        errStr << ": unknown error";
    }

  return( errStr.c_str() );
}


std::ostream &
MesgQueue::dumpInfo(
  std::ostream &    dest,
  const char *	    prefix
  ) const
{

  if( ! MesgQueue::good() )
    dest << prefix << "Error: " << MesgQueue::error() << '\n';
  else
    dest << prefix << "Good" << '\n';

  dest << prefix << "key filename:  " << keyFileName << '\n'
       << prefix << "proj:          " << keyProj << '\n'
       << prefix << "key:           " << key << '\n'
       << prefix << "queue id:      " << queueId << '\n'
       << prefix << "queue flags:   "
       << std::setbase( 8 ) << queueFlags << std::setbase( 0 ) << '\n'
    ;

  struct msqid_ds   qData;

  if( msgctl( queueId, IPC_STAT, &qData ) >= 0 )
    {
      User	creator( (uid_t) qData.msg_perm.cuid );
      UserGroup	creatorGroup( (gid_t) qData.msg_perm.cgid );

      User	user( (uid_t) qData.msg_perm.uid );
      UserGroup group( (gid_t) qData.msg_perm.gid );

      DateTime	lastSend( qData.msg_stime );
      DateTime  lastRecv( qData.msg_rtime );

      dest << prefix << "q.bytes    " << qData.msg_cbytes << '\n'
	   << prefix << "q.count    " << qData.msg_qnum << '\n'
	   << prefix << "q.max bytes: " << qData.msg_qbytes << '\n'
	   << prefix << "q.last send pid:  " << qData.msg_lspid << '\n'
	   << prefix << "q.last recv pid:  " << qData.msg_lrpid << '\n'
	   << prefix << "q.last send time: " << lastSend << '\n'
	   << prefix << "q.last recv time: " << lastRecv << '\n'
	   << prefix << "q.creator:        " << creator.getName()
	   << '(' << creator.getUID() << ")\n"
	   << prefix << "q.creator group:  " << creatorGroup.getName()
	   << '(' << creatorGroup.getGID() << ")\n"
	   << prefix << "q.user:           " << user.getName()
	   << '(' << user.getUID() << ")\n"
	   << prefix << "q.group:          " << group.getName()
	   << '(' << group.getGID() << ")\n"
	   << prefix << "permissions:      "
	   << FileModeString( qData.msg_perm.mode ) << '\n'
	;
    }
  else
    {
      dest << prefix << "msgctl failed - "
	   << strerror( errno ) << " - NO mesg queue data available.\n";
    }

  return( dest );
}

bool
MesgQueue::setError( ErrorNum errNum, int osErr )
{
  errorNum = errNum;
  osErrno  = osErr;

  return( good() );
}

}; // namespace clue
