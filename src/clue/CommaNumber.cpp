// 2004-04-02 (cc) Paul Houghton - (paul4hough@gmail.com)

#include "Clue.hpp"
#include "bit"
#include <iomanip>

namespace clue {

std::ostream &
CommaNumber(
  std::ostream &	dest,
  long		num,
  size_t	width,
  char		fillChar,
  size_t	decimalPlaces
  )
{

  static const char CharDigits[] = "0123456789";

  char buf[ ( 2 * ( sizeof( unsigned long ) * CHAR_BIT ) + 5 ) ];
  int  len = sizeof( buf ) - 2;
  int  pos = len;

  buf[ len + 1 ] = 0;

  unsigned long value( num );
  unsigned short digits( 0 );
  if( decimalPlaces > 0 ) {
    for( ; value > 0 && digits < decimalPlaces;
	 value /= 10, ++ digits, -- pos ) {
      buf[ pos ] = CharDigits[ value % 10 ];
    }
    for( ;digits < decimalPlaces; ++ digits, -- pos ) {
      buf[ pos ] = '0';
    }
    buf[ pos -- ] = '.';
    ++ digits;
    digits %= 3;

  }

  if( value == 0 ) {
    buf[ pos -- ] = '0';
  } else {

    for( ; value > 0;
	 value /= 10, ++ digits, -- pos ) {
      if( digits == 3 ) {
	buf[ pos -- ] = ',';
	digits = 0;
      }
      buf[ pos ] = CharDigits[ value % 10 ];
    }
  }

  if( width > 0 ) {
    char prevFill;
    prevFill = dest.fill( fillChar );
    dest << std::setw( width ) << &(buf[pos + 1]);
    dest.fill( prevFill );
  } else {
    dest << &(buf[pos + 1]);
  }

  return( dest );
}

}
