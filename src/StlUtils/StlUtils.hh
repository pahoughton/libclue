#ifndef _Common_plus_hh_
#define _Common_plus_hh_
//
// File:        Common++.hh
// Desc:        
//              
//
// Author:      Paul Houghton x2309 - (houghton@shoe)
// Created:     02/18/94 06:45
//
// Revision History:
//
// 
// $Log$
// Revision 1.1  1994/06/06 13:19:34  houghton
// Lib Clue beta version used for Rating 1.0
//
//

#include <ctype.h>
#include <stdlib.h>
#include <Common.h>
#include <iostream.h>




inline long
min( long v1, long v2 )
{
  return( ( v1 < v2 ) ? v1 : v2 );	
}

inline long
max( long v1, long v2 )
{
  return( ( v1 > v2 ) ? v1 : v2 );	
}

//
// Inline methods
//

inline int
StrToInt( const char * str, int base = 0,  int len = 0)
{
  return( StringToInt( str, base, len ) );
}
  

inline char
CharToShort( char c )
{
  return( isdigit( c ) ? c - '0' : -1 );
}
    
inline char
TwoCharToShort( const char * str )
{
  if( isdigit( str[0] ) && isdigit( str[1] ) )
    {
      return( ( (str[0] - '0') * 10 ) + (str[1] - '0') );
    }
  else
    {
      return( -1 );
    }		 
}


inline void
IntToString( char * dest, size_t destSize, int val )
{
  int srcValue = val;
  
  for( int i = destSize - 1; i >= 0; i-- )
    {
      dest[i] = srcValue % 10 + '0';
      srcValue /= 10;
    }
}
inline unsigned long
UnionOf(
    long startOne,
    long durOne,
    long startTwo,
    long durTwo
    )
{
#ifdef DEBUG_UO
  
  cout << "s1 " << startOne << " s2 " << startTwo
       << " d1 " << durOne << " d2 " << durTwo
       << " e1 " << startOne + durOne
       << " e2 " << startTwo + durTwo
       << endl;

#endif
  
  if( startTwo <= startOne + durOne &&
      startTwo + durTwo >= startOne )
    {
#ifdef DEBUG_UO
      cout << "Is In!" << endl;

      cout << labs( startOne - startTwo ) << endl;
      cout << labs( (startTwo + durTwo ) - (startOne + durOne) )<< endl;
      cout << durTwo + durOne << endl;
		   
#endif
      return( ( (durTwo + durOne) -
		( labs( startOne - startTwo ) +
		  labs( (startTwo + durTwo ) - (startOne + durOne) ) )
		) / 2 );
    }
  else
    {
      return( 0 );
    }
}
      
       
inline unsigned long
UnionOf(
    unsigned long startOne,
    unsigned long durOne,
    unsigned long startTwo,
    unsigned long durTwo,
    unsigned long frequency
    )
{
  unsigned long  unionSum = 0;
  unsigned long  startOfTwo = startTwo;
  unsigned long  durOfTwo = durTwo;
  unsigned long  endOfTwo = min( durTwo, frequency - startTwo);
  
  while( endOfTwo > 0 )
    {
      unionSum += UnionOf( startOne, durOne, startOfTwo, endOfTwo );
      startOfTwo = 0;
      durOfTwo -= endOfTwo;
      endOfTwo = min( frequency, durOfTwo );
    }
      
  return( unionSum );
}
      

#endif // ! def _Common_plus_hh_ 
//
//              This software is the sole property of
// 
//                 The Williams Companies, Inc.
//                        1 Williams Center
//                          P.O. Box 2400
//        Copyright (c) 1994 by The Williams Companies, Inc.
// 
//                      All Rights Reserved.  
// 
//
