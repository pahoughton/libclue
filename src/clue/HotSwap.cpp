// 1999-05-04 (cc) Paul Houghton <paul4hough@gmail.com>

#include "HotSwap.hpp"
#include <FileStat.hpp>

#include <cstdio>

#include <unistd.h>

namespace clue {

const char * HotSwap::ErrorDesc[] =
{
  "ok",
  "not a symbolic link",
  0
};


HotSwap::HotSwap(
  const FilePath &	lockFileName,
  std::ios::openmode    lockMode
  )
  : lockFn( lockFileName ),
    filelock( lockFn, lockMode ),
    errorNum( E_OK ),
    osErrno( 0 )
{
  if( ! sem.open( lockFn ) )
    {
      // could not open sem, try to create
      if( ! sem.create( lockFn,
			' ',
			1,
			(IPC_CREAT | IPC_EXCL | 0664) ) )
	{
	  // could not create, some one else probably already did
	  // wait a second and try again.
	  sleep( 1 );
	  if( ! sem.open( lockFn ) )
	    return;
	}
    }
}

HotSwap::~HotSwap( void )
{
}

bool
HotSwap::lock( void )
{

  if( sem.islocked() )
    {
      if( ! sem.waitfor() )
	return( false );
    }

  if( ! filelock.lockread() )
    return( false );

  return( true );
}

bool
HotSwap::waitForSwap( void )
{
  if( ! filelock.good() )    return( false );
  if( ! filelock.unlock() )   return( false );
  if( ! sem.waitfor() )      return( false );
  if( ! filelock.lockread() ) return( false );

  return( true );
}

bool
HotSwap::check( void )
{
  return( sem.islocked() );
}

bool
HotSwap::swapLock( void )
{
  if( ! sem.lock( false ) )
    return( false );

  if( ! filelock.lockwrite() )
    {
      sem.unlock();
      return( false );
    }

  return( true );
}

bool
HotSwap::swapUnLock( void )
{
  if( sem.good() )
    {
      if( ! filelock.unlock() )
	{
	  sem.unlock();
	  return( false );
	}

      if( ! sem.unlock() )
	return( false );
    }

  return( true );
}

bool
HotSwap::swap(
  const FilePath &  linkName,
  const FilePath &  linkDest
  )
{
  // use absolute file names.
  FilePath  absLinkDest;

  if( linkDest[0] != '/' )
    {
      char cwd[1024];

      if( ! getcwd( cwd, sizeof( cwd ) ) )
	return( setErrorDesc( errno, "getcwd" ) );

      absLinkDest << cwd << linkDest.dirSep() << linkDest ;
    }
  else
    {
      absLinkDest = linkDest;
    }

  FileStat  linkStat( linkName, true );

  bool	    linkExists;

  if( linkStat.good() )
    {
      linkExists = true;

      if( ! linkStat.isLink() )
	return( setErrorFn( E_NOT_LINK, linkName ) );
    }
  else
    {
      linkExists = false;
    }

  // only do locking if a link already exists

  if( linkExists )
    {
      if( ! swapLock() )
	return( false );

      // ok, all locked up.

      if( remove( linkName ) )
	{
	  setErrorFn( errno, linkName );
	  filelock.unlock();
	  sem.unlock();
	  return( false );
	}
    }

  if( symlink( absLinkDest, linkName ) )
    {
      setErrorFnDesc( errno, linkName, "creating link" );
      filelock.unlock();
      sem.unlock();
      return( false );
    }

  if( linkExists )
    {
      if( ! swapUnLock() )
	return( false );
    }

  return( true );
}

bool
HotSwap::good( void ) const
{
  return( filelock.good()
	  && sem.good()
	  && osErrno == 0
	  && errorNum == E_OK );
}

const char *
HotSwap::error( void ) const
{
  static Str errStr;

  errStr = "HotSwap";

  if( good() )
    {
      errStr << ": ok";
    }
  else
    {
      size_t eSize = errStr.size();

      if( ! filelock.good() )
	errStr << ": " << filelock.error();

      if( ! sem.good() )
	errStr << ": " << sem.error();

      if( errorFileName.size() )
	{
	  errStr << ": '" << errorFileName << "' -";
	  if( errorDesc.size() )
	    errStr << errorDesc;
	}
      else
	{
	  if( errorDesc.size() )
	    errStr << ": " << errorDesc;
	  else
	    errStr << ": ";
	}

      if( errorNum != E_OK )
	errStr << " " << ErrorDesc[ errorNum ];

      if( osErrno )
	errStr << " " << strerror( osErrno );

      if( eSize == errStr.size() )
        errStr << ": unknown error";
    }

  return( errStr.c_str() );
}


std::ostream &
HotSwap::dumpInfo(
  std::ostream &	dest,
  const char *	    prefix
  ) const
{

  if( ! HotSwap::good() )
    dest << prefix << "Error: " << HotSwap::error() << '\n';
  else
    dest << prefix << "Good" << '\n';


  dest << prefix << "lockFn:  '" << lockFn << "'\n";

  Str pre;

  pre = prefix;
  pre << "filelock: ";
  filelock.dumpInfo( dest, pre );

  pre = prefix;
  pre << "sem:";
  sem.dumpInfo( dest, pre );

  return( dest );
}

bool
HotSwap::setErrorDesc( int osErr, const char * desc )
{
  osErrno = osErr;
  errorDesc = desc;
  return( good() );
}

bool
HotSwap::setErrorFn( ErrorNum err, const char * fn )
{
  errorNum	= err;
  errorFileName	= fn;
  return( good() );
}

bool
HotSwap::setErrorFn( int osErr, const char * fn )
{
  osErrno	= osErr;
  errorFileName	= fn;

  return( good() );
}

bool
HotSwap::setErrorFnDesc( int osErr, const char * fn, const char * desc )
{
  osErrno	= osErr;
  errorFileName	= fn;
  errorDesc	= desc;

  return( good() );
}

}; // namespace clue
