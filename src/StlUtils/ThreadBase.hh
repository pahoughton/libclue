#ifndef _ThreadBase_hh_
#define _ThreadBase_hh_
//
// File:        ThreadBase.hh
// Project:	StlUtils (%PP%)
// Item:   	%PI% (%PF%)
// Desc:        
//
//  Base class for creating threads.
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul_houghton@wiltel.com)
// Created:     04/25/96 06:16
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    %PO%
//  Last Mod:	    %PRT%
//  Version:	    %PIV%
//  Status: 	    %PS%
//
// %PID%

#if !defined( STLUTILS_SHORT_FN )
#include <StlUtilsConfig.hh>
#else
#include <StlUtilsCfg.hh>
#endif

#if defined( STLUTILS_DEBUG )
#define inline
#endif


class ThreadBase
{

public:

  ThreadBase( bool  detach );

  virtual ~ThreadBase( void );

  virtual bool	start( void );

  inline void		attach( void );
  inline void		detach( void );
  
  bool		join( void );
  
  virtual bool	    	good( void ) const;
  virtual const char * 	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *  getVersion( bool withPrjVer = true ) const;
  virtual ostream &     dumpInfo( ostream &	dest = cerr,
				  const char *  prefix = "    ",
                                  bool          showVer = true ) const;

  static const ClassVersion version;
  
protected:

  virtual bool	main( void ) = 0;

#if defined( STLUTILS_THREADS )
  pthread_t	threadId;
#endif
  bool		cleanup;
  int		errorNum;
  
private:

  static void * threadEntry( void * );
  
  ThreadBase( const ThreadBase & from );
  ThreadBase & operator =( const ThreadBase & from );

};

#if !defined( inline )
#if !defined( STLUTILS_SHORT_FN )
#include <ThreadBase.ii>
#else
#include <ThreadBase.ii>
#endif
#else
#undef inline
#endif


//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	ThreadBase	class
//
//  Constructors:
//
//  	ThreadBase( );
//
//  Destructors:
//
//  Public Interface:
//
//	virtual ostream &
//	toStream( ostream & dest ) const
//	    output class as a string to dest (used by operator <<)
//
//  	virtual Bool
//  	good( void ) const;
//  	    Return true if there are no detected errors associated
//  	    with this class, otherwise false.
//
//  	virtual const char *
//  	error( void ) const
//  	    Return a string description of the state of the class.
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. ThreadBase )
//
//  	virtual const char *
//  	getVersion( bool withPrjVer = true ) const;
//  	    Return the version string of this class.
//
//	virtual ostream &
//	dumpInfo( ostream & dest, const char * prefix, bool showVer )
//	    output detail info to dest. Includes instance variable
//	    values, state info & version info.
//
//	static const ClassVersion
//	version
//	    class & project version information. (see ClassVersion.hh)
//
//  Protected Interface:
//
//  Private Methods:
//
//  Other Associated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const ThreadBase & obj );
//

// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 5.2  2001/07/26 19:28:58  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:18  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:13:07  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:08:57  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:24:25  houghton
// Changed to Release 3
//
// Revision 2.2  1996/11/04 14:34:35  houghton
// Changed to be compilable even if STLUTILS_THREADS is not defined.
//
// Revision 2.1  1996/04/27 13:11:52  houghton
// Initial version.
//
//
#endif // ! def _ThreadBase_hh_ 

