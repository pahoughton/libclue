#ifndef _AppParam_hh_
#define _AppParam_hh_
//
// File:        AppParam.hh
// Project:	Clue
// Desc:        
//
//
//
// Author:      Paul A. Houghton - (paul.houghton@wcom.com)
// Created:     09/12/97 16:36
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

#include <Param.hh>
#include <FilePath.hh>

class AppParam : public Param
{

public:

  AppParam( int & argv, char ** argc, const char * ver = 0 );

  ~AppParam( void );

  const FilePath &  lockFn( void ) const { return( lockFnV ); };
  bool		    createLockFile( void ) const { return( createLockFileV ); };
  long		    swapCount( void ) const { return( swapCountV ); };
  int		    sleepTime( void ) const { return( sleepTimeV ); };
  
  bool		parseArgs( void );
  bool		parseArgs( int argc, char * argv[] );

protected:

  FilePath  lockFnV;
  bool	    createLockFileV;
  long	    swapCountV;
  int	    sleepTimeV;
  
private:

  AppParam( const AppParam & copyFrom );
  AppParam & operator=( const AppParam & assignFrom );

};

extern AppParam * App;


//  Data Types: - data types defined by this header
//
//  	AppParam	class
//
//  Constructors:
//
//  	AppParam( );
//
//  Destructors:
//
//  Public Interface:
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. AppParam )
//
//  	virtual Bool
//  	good( void ) const;
//  	    Returns true if there are no detected errors associated
//  	    with this class, otherwise FALSE.
//
//  	virtual const char *
//  	error( void ) const
//  	    Returns as string description of the state of the class.
//
//  Protected Interface:
//
//  Private Methods:
//
//  Other Associated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const AppParam & obj );
//
// Revision Log:
//
// $Log$
// Revision 1.1  1997/09/16 11:31:14  houghton
// Initial Version.
//
//

#endif // ! def _AppParam_hh_ 
