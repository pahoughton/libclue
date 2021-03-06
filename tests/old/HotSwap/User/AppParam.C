//
// File:        AppParam.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for AppParam
//  
// Author:      Paul A. Houghton - (paul4hough@gmail.com)
// Created:     09/13/97 12:28
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include "AppParam.hh"

AppParam::AppParam(
  int &		mainArgc,
  char **	mainArgv,
  const char *	mainVer
  )
  : Param( mainArgc, mainArgv, mainVer, true, "ERROR | WARN | INFO" ),
    lockFnV( "../data/hotswap" ),
    swapCountV( 1 ),
    sleepTimeV( 5 )
{
  parseArgs();
}

AppParam::~AppParam( void )
{
}

bool
AppParam::parseArgs( int pArgc, char * pArgv[] )
{
  bool status = Param::parseArgs( pArgc, pArgv );

  return( status ? parseArgs() : status );
}

bool
AppParam::parseArgs( void )
{
  bool status = Param::parseArgs();

  status &= argInt( sleepTimeV,
		     "sleep seconds",
		     "s",
		     "SLEEP_SEC" );
  
  status &= argLong( swapCountV,
		     "swap count",
		     "n",
		     "SWAP_COUNT" );
  
  // status &= argStr( varV, "desc", "argid", "envVar" );

  return( status );
}

// Revision Log:
//
// $Log$
// Revision 6.2  2011/12/30 23:57:50  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:53  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:32  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:58  houghton
// Changed to Version 4
//
// Revision 1.2  1997/09/17 11:10:19  houghton
// Changed: renamed library to StlUtils.
//
// Revision 1.1  1997/09/16 11:31:26  houghton
// Initial Version.
//
//
