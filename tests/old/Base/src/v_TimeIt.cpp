//
// File:        tTimeIt.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for tTimeIt
//  
// Author:      Paul A. Houghton - (paul4hough@gmail.com)
// Created:     07/08/97 08:11
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include <TestConfig.hh>
#include <LibTest.hh>

bool	tTimeIt01( LibTest & tester );

bool
tTimeIt( LibTest & tester )
{
  TESTP( tTimeIt01( tester ) );

  return( true );
}


// Revision Log:
//
// $Log$
// Revision 6.2  2011/12/30 23:57:48  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:53  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:31  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:14:51  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:10:14  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1997/07/11 15:57:08  houghton
// Initial Version.
//
//
