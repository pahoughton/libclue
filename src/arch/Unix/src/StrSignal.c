/*********************************************************************
 *
 * File:        StrSignal.c
 * Project:	StlUtils (%PP%)
 * Item:   	%PI% (%PF%)
 * Desc:
 *
 *  Return a string containing the name of a signal.
 *
 * Notes:
 *
 * Author:	Paul Houghton - (paul.houghton@wcom.com)
 * Created:	01/30/98 06:27
 *
 * Revision History: (See end of file for Revision Log)
 *
 *  Last Mod By:    %PO%
 *  Last Mod:	    %PRT%
 *  Version:	    %PIV%
 *  Status: 	    %PS%
 *
 *********************************************************************/

#include "StrSignal.h"
#include "_SignalStrings.h"
#include <stdio.h>

#define ArraySize( _a_ ) ( sizeof( _a_ ) / sizeof( _a_[0] ) )

static char	SigNumString[32];

const char *
StrSignal( int sig )
{

  if( sig < ArraySize( SignalStrings ) )
    {
      return( SignalStrings[ sig ] );
    }
  else
    {
      sprintf( SigNumString, "SIGNUM_%d", sig );
      return( SigNumString );
    }
}

/*
 *
 * Revision Log:
 *
 * 
 * %PL%
 * 
 * $Log$
 * Revision 5.2  2001/07/26 19:28:57  houghton
 * *** empty log message ***
 *
 * Revision 5.1  2000/05/25 10:33:23  houghton
 * Changed Version Num to 5
 *
 * Revision 1.1  1998/02/02 15:32:27  houghton
 * Initial version.
 *
 *
 */
