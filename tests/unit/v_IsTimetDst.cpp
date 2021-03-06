// 2005-09-09 (cc) <paul4hough@gmail.com>

#include <clue/Clue.hpp>
#include <clue/DateTime.hpp>
#include <clue/DateTimeUtils.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

static valid::verify verify("clue::IsTimetDst");
using namespace clue;

bool
v_IsTimetDst( void )
{

  {
    /*
      April 2001
       S  M Tu  W Th  F  S
       1  2  3  4  5  6  7
       8  9 10 11 12 13 14
      15 16 17 18 19 20 21
      22 23 24 25 26 27 28
      29 30
    */

    DateTime t( 2001, 4, 1, 0, 0, 0 );

    TEST( IsTimetDst( t ) == false );
    t.addMin( 59 );
    TEST( IsTimetDst( t ) == false );
    t.addHour( 1 );
    TEST( IsTimetDst( t ) == false );
    t.addMin( 1 );
    TEST( IsTimetDst( t ) == true );
    for( int d = 2; d < 30; ++d ) {
      t.addDay( 1 );
      TEST( IsTimetDst( t ) == true );
    }
    t.set( 2001,4,30,23,59,59 );
    TEST( IsTimetDst( t ) == true );
    t.addHour( 1 );
    TEST( IsTimetDst( t ) == true );
    for( int m = 5; m < 10; ++ m ) {
      t.set( 2001, m, 1, 0, 0, 0 );
      TEST( IsTimetDst( t ) == true );
    }
    /*
      October 2001
       S  M Tu  W Th  F  S
          1  2  3  4  5  6
       7  8  9 10 11 12 13
      14 15 16 17 18 19 20
      21 22 23 24 25 26 27
      28 29 30 31
    */

    t.set( 2001, 10, 1, 0, 0, 0 );
    TEST( IsTimetDst( t ) == true );
    t.set( 2001, 10, 28, 0, 0, 0 );
    TEST( IsTimetDst( t ) == true );
    t.addMin( 59 );
    TEST( IsTimetDst( t ) == true );
    t.addMin( 62 );
    TEST( IsTimetDst( t ) == false );
    t.addDay( 1 );
    TEST( IsTimetDst( t ) == false );
    t.addDay( 1 );
    TEST( IsTimetDst( t ) == false );
    t.addDay( 1 );
    TEST( IsTimetDst( t ) == false );
    t.addDay( 1 );
    TEST( IsTimetDst( t ) == false );
    t.addDay( 1 );
    TEST( IsTimetDst( t ) == false );
    t.addDay( 1 );
    TEST( IsTimetDst( t ) == false );
  }
  {
    /*
      April 2002
       S  M Tu  W Th  F  S
          1  2  3  4  5  6
       7  8  9 10 11 12 13
      14 15 16 17 18 19 20
      21 22 23 24 25 26 27
      28 29 30
    */

    DateTime t( 2002, 4, 1, 0, 0, 0 );

    TEST( IsTimetDst( t ) == false );
    t.addDay( 1 );
    TEST( IsTimetDst( t ) == false );
    t.set( 2002, 4, 7, 0, 0, 0 );
    TEST( IsTimetDst( t ) == false );
    t.addHour( 1 );
    TEST( IsTimetDst( t ) == false );
    t.addMin( 59 );
    TEST( IsTimetDst( t ) == false );
    t.addMin( 2 );
    TEST( IsTimetDst( t ) == true );
    t.addHour( 1 );
    TEST( IsTimetDst( t ) == true );

    t.set( 2001,4,30,23,59,59 );
    TEST( IsTimetDst( t ) == true );
    t.addHour( 1 );
    TEST( IsTimetDst( t ) == true );
    for( int m = 5; m < 10; ++ m ) {
      t.set( 2001, m, 1, 0, 0, 0 );
      TEST( IsTimetDst( t ) == true );
    }

    /*
      October 2002
       S  M Tu  W Th  F  S
             1  2  3  4  5
       6  7  8  9 10 11 12
      13 14 15 16 17 18 19
      20 21 22 23 24 25 26
      27 28 29 30 31
    */
    t.set( 2002, 10, 26, 0, 0, 0 );
    TEST( IsTimetDst( t ) == true );
    t.addDay( 1 );
    TEST( IsTimetDst( t ) == true );
    t.addMin( 59 );
    TEST( IsTimetDst( t ) == true );
    t.addMin( 62 );
    TEST( IsTimetDst( t ) == false );
    t.addHour( 24 );
    TEST( IsTimetDst( t ) == false );
    t.set( 2002, 10, 29, 0, 0, 0 );
    TEST( IsTimetDst( t ) == false );
    t.addDay( 1 );
    TEST( IsTimetDst( t ) == false );
    t.addDay( 1 );
    TEST( IsTimetDst( t ) == false );
    t.addDay( 1 );
    TEST( IsTimetDst( t ) == false );
    t.addDay( 1 );
    TEST( IsTimetDst( t ) == false );
    t.addDay( 1 );
    TEST( IsTimetDst( t ) == false );
  }
  return( verify.is_valid() );
}
