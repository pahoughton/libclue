/* 1996-10-30 (cc) <paul4hough@gmail.com>
  Test the following Bitmask methods.

    bit operator [] ( size_t );
    bit operator () ( size_t );
    bool operator [] ( size_t ) const;
    bool operator () ( size_t ) const;
    operator = ( unsigned long )
    operator =  ( const bit & )
    operator &= ( const bit & )
    operator |= ( const bit & )
    operator |= ( const bit & )
    operator ^= ( const bit & )
    operator &= ( const Bitmask & )
    operator |= ( const Bitmask & )
    operator ^= ( const Bitmask & )
    operator == ( const Bitmask & ) const
    operator <  ( const Bitmask & ) const
    operator <= ( const Bitmask & ) const
    operator >  ( const Bitmask & ) const
    operator >= ( const Bitmask & ) const
    operator == ( unsigned long ) const
    operator != ( unsigned long ) const
    operator <  ( unsigned long ) const
    operator <= ( unsigned long ) const
    operator >  ( unsigned long ) const
    operator >= ( unsigned long ) const
    operator bool ( void ) const
    operator unsigned long ( void ) const
    toStream( ostream & ) const
    fromStream( istream & );
    dumpInfo( ostream & ) const
    bit::operator bool () const;
    bit::pos( void ) const;
    bit::toStream( ostream & ) const
    bit::dumpinfo( ostream &, const char *, bool )

    static const bit b00;
    static const bit b01;
    static const bit b02;
    static const bit b03;
    static const bit b04;
    static const bit b05;
    static const bit b06;
    static const bit b07;
    static const bit b08;
    static const bit b09;
    static const bit b10;
    static const bit b11;
    static const bit b12;
    static const bit b13;
    static const bit b14;
    static const bit b15;
    static const bit b16;
    static const bit b17;
    static const bit b18;
    static const bit b19;
    static const bit b20;
    static const bit b21;
    static const bit b22;
    static const bit b23;
    static const bit b24;
    static const bit b25;
    static const bit b26;
    static const bit b27;
    static const bit b28;
    static const bit b29;
    static const bit b30;
    static const bit b31;
    static const Bitmask all;
    static const size_t maxPos;

    ::operator << ( ostream &, const Bitmask & );
    ::operator >> ( istream &, Bitmask & );
    ::operator << ( ostream &, const Bitmask::bit & )

  Also uses the following methods.

    bit::pos( void ) const;
    bit::operator =  ( bool rhs )
    bit::operator bool () const
*/

#include <clue/Bitmask.hpp>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <sstream>

static valid::verify verify("clue::bitmask02");
using namespace clue;

bool
v_bitmask02( void )
{
  {
    // bit operator [] ( size_t );
    // bit operator () ( size_t );

    //	uses - bit::pos( void ) const;
    //  uses - bit::operator bool () const;

    Bitmask t;

    for( size_t p = 0; p < 16; p++ )
      {
	TEST( t[ p ].pos() == p );
	TEST( t( p ).pos() == p );
	TEST( ! t[ p ] );
	TEST( ! t( p ) );

	t.set( p );

	TEST( t[ p ] );
	TEST( t( p ) );

	t[p] = false;

	TEST( ! t[ p ] );
	TEST( ! t( p ) );
	TEST( ! t.test( p ) );

	t( p ) = true;

	TEST( t[ p ] );
	TEST( t( p ) );
      }
  }

  {
    // bool operator [] ( size_t ) const;
    // bool operator () ( size_t ) const;

    const Bitmask t( 0x1824 );

    TEST( ! t[1] );
    TEST( ! t(1) );
    TEST( t[2] );
    TEST( t(2) );
    TEST( t[5] );
    TEST( t(5) );
    TEST( t[11] );
    TEST( t(11) );
    TEST( t[12] );
    TEST( t(12) );
    TEST( ! t[13] );
    TEST( ! t(13) );
  }


  {
    // operator = ( unsigned long )

    Bitmask t;

    t = 0x1080;
    TEST( t.to_ulong() == 0x1080 );
  }

  {
    // operator =  ( const bit & )

    Bitmask t;
    Bitmask s( 0x124f );

    t = s(9);
    TEST( t.to_ulong() == 0x0200 );

    t.set(4);
    TEST( t.to_ulong() == 0x0210 );

    t = s(4);
    TEST( t.to_ulong() == 0x000 );

    t = s(12);
    TEST( t.to_ulong() == 0x1000 );

    // operator &= ( const bit & )

    t &= s(12);
    TEST( t.to_ulong() == 0x1000 );

    t &= s(1);
    TEST( t.to_ulong() == 0x1000 );

    t.set( 2 );
    t &= s(2);
    TEST( t.to_ulong() == 0x1004 );

    // operator |= ( const bit & )

    t |= s(6);
    TEST( t.to_ulong() == 0x1044 );

    t |= s(16);
    TEST( t.to_ulong() == 0x1044 );

    t.set(16);
    t |= s(16);
    TEST( t.to_ulong() == 0x11044 );

    // operator ^= ( const bit & )

    // 1 1
    t ^= s(2);
    TEST( t.to_ulong() == 0x11040 );

    // 0 1
    t ^= s(1);
    TEST( t.to_ulong() == 0x11042 );

    // 1 0
    t ^= s(16);
    TEST( t.to_ulong() == 0x11042 );

    // 0 0
    t ^= s(4);
    TEST( t.to_ulong() == 0x11042 );
  }

  {
    // operator &= ( const Bitmask & )
    // operator |= ( const Bitmask & )
    // operator ^= ( const Bitmask & )

    Bitmask t(0x1f9f);
    Bitmask rhs;

    rhs.set( 7 );
    t &= rhs;

    TEST( t.to_ulong() == 0x80 );

    rhs.set( 0 );
    t |= rhs;

    TEST( t.to_ulong() == 0x81 );

    rhs.reset();
    rhs.set( 7 );
    rhs.set( 15 );
    t ^= rhs;

    TEST( t.to_ulong() == 0x8001 );
  }

  {
    // operator == ( const Bitmask & ) const
    // operator <  ( const Bitmask & ) const
    // operator <= ( const Bitmask & ) const
    // operator >  ( const Bitmask & ) const
    // operator >= ( const Bitmask & ) const
    // operator == ( unsigned long ) const
    // operator != ( unsigned long ) const
    // operator <  ( unsigned long ) const
    // operator <= ( unsigned long ) const
    // operator >  ( unsigned long ) const
    // operator >= ( unsigned long ) const

    const Bitmask t( 0x10 );
    const Bitmask te( 0x10 );
    const Bitmask tl( 0x04 );
    const Bitmask tm( 0x20 );

    unsigned int le = 0x10;
    unsigned int ll = 0x04;
    unsigned int lm = 0x20;

    TEST( t == te );
    TEST( t != tl );
    TEST( t <  tm );
    TEST( t <= tm );
    TEST( t <= te );
    TEST( t >  tl );
    TEST( t >= tl );
    TEST( t >= te );

    TEST( t == le );
    TEST( t != lm );
    TEST( t <  lm );
    TEST( t <= lm );
    TEST( t <= le );
    TEST( t >  ll );
    TEST( t >= ll );
    TEST( t >= le );
  }

  {
    // operator bool ( void ) const
    // operator unsigned long ( void ) const

    const Bitmask t1;
    const Bitmask t2( Bitmask::b03 );

    TEST( ! (t1 == true) );
    TEST( t2 );

    TEST( (unsigned)t1  == 0x0U );
    TEST( (unsigned)t2 == 0x08U );
  }


  {
    // toStream( ostream & ) const
    // fromStream( istream & );
    const Bitmask   tw(0xf1248);
    Bitmask	    tr(0xffffffff);

    {
      std::stringstream tStrm;

      TEST( tw != tr );
      TEST( tw.toStream( tStrm ).good() );
      TEST( ! tr.fromStream( tStrm ).good() );
      TEST( tStrm.rdstate() == ( std::ios::eofbit ) );
      TEST( tw == tr );
    }

    {
      std::stringstream tStrm;

      TEST( tw.toStream( tStrm ).good() );

      TEST( ! strncmp( tw.to_string(), tStrm.str().c_str(), 32 ) );

    }

    {
      std::stringstream tStrm;

      tStrm << "0101    1111";

      TEST( tr.fromStream( tStrm ).good() );
      TEST( tr.to_ulong() == 0x05 );


      TEST( ! tr.fromStream( tStrm ).good() );
      /*
	cerr << "\nWHAT? : '" << tStrm.rdstate()
	   << "' eof(" << ios::eofbit
	   << ") tr '" << tr
	   << "'."
	   << endl;
      */
      TEST( tStrm.rdstate() == ( std::ios::eofbit ) );
      TEST( tr.to_ulong() == 0x0f );
    }

    {
      std::stringstream tStrm;

      tStrm << "2222";
      TEST( ! tr.fromStream( tStrm ).good() );
      TEST( tStrm.fail() );
      TEST( ! tStrm.eof() );
    }

  }

  {
    // dumpInfo( ostream & ) const

    const Bitmask t(0x1248cdef );
    std::stringstream tStrm;

    t.dumpInfo( tStrm );
    TEST( tStrm.good() );
  }

  {
    // bit::operator bool () const;
    // bit::pos( void ) const;

    // static const bit b00;
    // static const bit b01;
    // static const bit b02;
    // static const bit b03;
    // static const bit b04;
    // static const bit b05;
    // static const bit b06;
    // static const bit b07;
    // static const bit b08;
    // static const bit b09;
    // static const bit b10;
    // static const bit b11;
    // static const bit b12;
    // static const bit b13;
    // static const bit b14;
    // static const bit b15;
    // static const bit b16;
    // static const bit b17;
    // static const bit b18;
    // static const bit b19;
    // static const bit b20;
    // static const bit b21;
    // static const bit b22;
    // static const bit b23;
    // static const bit b24;
    // static const bit b25;
    // static const bit b26;
    // static const bit b27;
    // static const bit b28;
    // static const bit b29;
    // static const bit b30;
    // static const bit b31;

    TEST( Bitmask::b00 == true );
    TEST( Bitmask::b00.pos() == 0 );

    TEST( Bitmask::b01 == true );
    TEST( Bitmask::b01.pos() == 1 );

    TEST( Bitmask::b02 == true );
    TEST( Bitmask::b02.pos() == 2 );

    TEST( Bitmask::b03 == true );
    TEST( Bitmask::b03.pos() == 3 );

    TEST( Bitmask::b04 == true );
    TEST( Bitmask::b04.pos() == 4 );

    TEST( Bitmask::b05 == true );
    TEST( Bitmask::b05.pos() == 5 );

    TEST( Bitmask::b06 == true );
    TEST( Bitmask::b06.pos() == 6 );

    TEST( Bitmask::b07 == true );
    TEST( Bitmask::b07.pos() == 7 );

    TEST( Bitmask::b08 == true );
    TEST( Bitmask::b08.pos() == 8 );

    TEST( Bitmask::b09 == true );
    TEST( Bitmask::b09.pos() == 9 );

    TEST( Bitmask::b10 == true );
    TEST( Bitmask::b10.pos() == 10 );

    TEST( Bitmask::b11 == true );
    TEST( Bitmask::b11.pos() == 11 );

    TEST( Bitmask::b12 == true );
    TEST( Bitmask::b12.pos() == 12 );

    TEST( Bitmask::b13 == true );
    TEST( Bitmask::b13.pos() == 13 );

    TEST( Bitmask::b14 == true );
    TEST( Bitmask::b14.pos() == 14 );

    TEST( Bitmask::b15 == true );
    TEST( Bitmask::b15.pos() == 15 );

    TEST( Bitmask::b16 == true );
    TEST( Bitmask::b16.pos() == 16 );

    TEST( Bitmask::b17 == true );
    TEST( Bitmask::b17.pos() == 17 );

    TEST( Bitmask::b18 == true );
    TEST( Bitmask::b18.pos() == 18 );

    TEST( Bitmask::b19 == true );
    TEST( Bitmask::b19.pos() == 19 );

    TEST( Bitmask::b20 == true );
    TEST( Bitmask::b20.pos() == 20 );

    TEST( Bitmask::b21 == true );
    TEST( Bitmask::b21.pos() == 21 );

    TEST( Bitmask::b22 == true );
    TEST( Bitmask::b22.pos() == 22 );

    TEST( Bitmask::b23 == true );
    TEST( Bitmask::b23.pos() == 23 );

    TEST( Bitmask::b24 == true );
    TEST( Bitmask::b24.pos() == 24 );

    TEST( Bitmask::b25 == true );
    TEST( Bitmask::b25.pos() == 25 );

    TEST( Bitmask::b26 == true );
    TEST( Bitmask::b26.pos() == 26 );

    TEST( Bitmask::b27 == true );
    TEST( Bitmask::b27.pos() == 27 );

    TEST( Bitmask::b28 == true );
    TEST( Bitmask::b28.pos() == 28 );

    TEST( Bitmask::b29 == true );
    TEST( Bitmask::b29.pos() == 29 );

    TEST( Bitmask::b30 == true );
    TEST( Bitmask::b30.pos() == 30 );

    TEST( Bitmask::b31 == true );
    TEST( Bitmask::b31.pos() == 31 );

  }

  {
    // static const Bitmask all;

    Bitmask t;

    t.set();

    TEST( t == t.all );
    TEST( t == Bitmask::all );

    for( int i = 0; i < 32; i++ )
      TEST( Bitmask::all.test(i) );
  }

  {
    // static const size_t maxPos;

    TEST( Bitmask::maxPos == 32 );
  }

  {
    // bit::toStream( ostream & ) const

    Bitmask t(0x8421);

    std::stringstream tStrm;

    Bitmask::b00.toStream( tStrm ) << " ";
    t(1).toStream( tStrm ) << " ";
    t(0).toStream( tStrm ) << std::ends;

    TEST( ! strcmp( tStrm.str().c_str(),
		     "true false true" ) );
  }

  {
    // bit::dumpinfo( ostream &, const char *, bool )
    std::stringstream tStrm;

    Bitmask::b16.dumpInfo( tStrm, " -> ");
  }

  {
    // ::operator << ( ostream &, const Bitmask & );
    // ::operator >> ( istream &, Bitmask & );

    const Bitmask   tw( 0x8421fedc );
    Bitmask	    tr(0xffffffff);

    {
      std::stringstream tStrm;

      TEST( tw != tr );
      tStrm << tw;
      tStrm >> tr;
      TEST( tw == tr );
    }

    {
      std::stringstream tStrm;

      tStrm << tw << std::ends;

      TEST( ! strcmp( tw.to_string(), tStrm.str().c_str() ) );
    }
  }
  {
    // ::operator << ( ostream &, const Bitmask::bit & )

    Bitmask t(0x8421);

    std::stringstream tStrm;

    tStrm << Bitmask::b00 << ' '
	  << t(1) << ' '
	  << t(0) << std::ends;

    TEST( ! strcmp( tStrm.str().c_str(),
		     "true false true" ) );
  }

  return( verify.is_valid() );
}
