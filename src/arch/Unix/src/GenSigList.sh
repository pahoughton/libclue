#!/bin/sh
#
# Title:        GenSigList.sh
# Project:	StlUtils (%PP%)
# Item:   	%PI% (%PF%)
# Desc:
# 
#   Generate SignalStrings source from system signal header file.
# 
# Notes:
# 
# Author:	Paul A. Houghton - (paul.houghton@wcom.com)
# Created:	08/05/97 07:15
#
# Revision History: (See end of file for Revision Log)
#
#   Last Mod By:    %PO%
#   Last Mod:	    %PRT%
#   Version:	    %PIV%
#   Status: 	    %PS%
# 
#  %PID%
# 

echo Generating SingalStrings into $2

cat > $2 <<'EOS'
#if !defined( _GENSIGLIST_ )
#define _GENSIGLIST_
/*
 * 
 * This file was generated by 'GenSigList.sh' version $Revision$
 *
 * DO NOT MODIFY
 *
 */

static const char * SignalStrings[] =
{
EOS

CC=$1

echo '#include <signal.h>' > /tmp/sigs$$.c

hdrs=`$CC -E /tmp/sigs$$.c | grep '[ 	]*#' | sed -n -e '/#ident/d' -e 's@.*"\(.*/.*\)".*@\1@' -e '/\//p' | grep -v "/tmp/sigs$$.c" | sort | uniq`

rm /tmp/sigs$$.c

rm sig.lst 2> /dev/null


for hdr in $hdrs ; do
  # echo -- Checking $hdr for sigs
  grep '^[ 	]*#[ 	]*define[ 	]*SIG[A-Z].*[ 	][ 	]*[0-9][0-9]*' $hdr | sed -e 's/.*\(SIG[^ 	]*\)[ 	][ 	]*\([0-9][0-9]*\).*/\2 \1/' | sort -n >> sig.lst
  # cat sig.lst
done


echo Found `wc -l sig.lst | sed -e 's/[^0-9]*\([0-9][0-9]*\)[^0-9]*/\1/'` signals.

cat >sig.awk <<'EOP'
BEGIN { maxsig = 0 }
NF == 2 {
  if( $1 > maxsig) { maxsig = $1 }
  sig_name[$1] = $2
  }
END {
  if( maxsig > 100 ) { maxsig = 100 }
  for( n = 0; n <= maxsig; n++ ) {
    if( sig_name[n]) {
      printf( "  \"%s\",\n", sig_name[n] )
    }
    else {
      printf( "  \"SIGNUM_%d\",\n", n )
    }
  }
  printf( "  \"SIG_unknown\"\n" )
}
EOP

# cat sig.lst

awk -f sig.awk < sig.lst >> $2

cat >> $2 <<'EOS'
};
#endif /* ! def _GENSIGLIST_ */
EOS

#
# $Log$
# Revision 5.2  2001/07/26 19:28:57  houghton
# *** empty log message ***
#
# Revision 5.1  2000/05/25 10:33:22  houghton
# Changed Version Num to 5
#
# Revision 4.3  2000/03/21 23:29:15  houghton
# Bug-Fix: was not picking up all sig names.
#
# Revision 4.2  1997/09/21 21:22:00  houghton
# Port(Sun5): have to filter out #indent lines.
#
# Revision 4.1  1997/09/17 15:13:31  houghton
# Changed to Version 4
#
# Revision 3.3  1997/09/17 11:09:19  houghton
# Changed: renamed library to StlUtils.
#
# Revision 3.2  1997/08/18 10:32:50  houghton
# Changed to limit the number of signals to 100, sun has one with a
#     value up around 8000.
#
# Revision 3.1  1997/08/08 13:25:30  houghton
# Initial Version.
#
#

# Local Variables:
# mode:ksh
# End:


#
# $Log$
# Revision 5.2  2001/07/26 19:28:57  houghton
# *** empty log message ***
#
# Revision 5.1  2000/05/25 10:33:22  houghton
# Changed Version Num to 5
#
# Revision 4.3  2000/03/21 23:29:15  houghton
# Bug-Fix: was not picking up all sig names.
#
# Revision 4.2  1997/09/21 21:22:00  houghton
# Port(Sun5): have to filter out #indent lines.
#
# Revision 4.1  1997/09/17 15:13:31  houghton
# Changed to Version 4
#
# Revision 3.3  1997/09/17 11:09:19  houghton
# Changed: renamed library to StlUtils.
#
# Revision 3.2  1997/08/18 10:32:50  houghton
# Changed to limit the number of signals to 100, sun has one with a
#     value up around 8000.
#
# Revision 3.1  1997/08/08 13:25:30  houghton
# Initial Version.
#
#

# Local Variables:
# mode:ksh
# End:
#! /bin/bash
