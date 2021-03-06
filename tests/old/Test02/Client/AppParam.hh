#ifndef _AppParam_hh_
#define _AppParam_hh_
//
// File:        AppParam.hh
// Desc:        
//
//
//  Quick Start: - short example of class usage
//
//
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     11/10/95 12:31
//
// Revision History:
//
// $Log$
// Revision 6.2  2011/12/30 23:57:51  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:54  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:33  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:15:03  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:10:22  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:27:58  houghton
// Changed to Release 3
//
// Revision 1.1  1995/11/17 16:59:48  houghton
// Initial Version.
//
//

#include <Param.hh>

class AppParam : public Param
{

public:

  AppParam( int & argv, char ** argc, const char * ver = 0 );

  ~AppParam( void );

  const Str &	server( void ) const { return vServer; };
  const Str &	client( void ) const { return vClient; };
  
  
protected:

private:

  Str	vServer;
  Str	vClient;
  
  AppParam( const AppParam & copyFrom );
  AppParam & operator=( const AppParam & assignFrom );

};

extern AppParam *   App;

//
// Inline methods
//

inline
AppParam::AppParam( int & argc, char ** argv, const char * ver )
  : Param( argc, argv, ver ),
    vServer( "WcfTest01" ),
    vClient( "StlUtils" )
{
  argStr( vServer, "CF Server name", "sn", "SERVERNAME" );  
  argStr( vClient, "CF Client name", "cn", "CLIENTNAME" ); 
}

inline
AppParam::~AppParam( void )
{
  
}

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

#endif // ! def _AppParam_hh_ 
