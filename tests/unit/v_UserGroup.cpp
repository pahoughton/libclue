// 1996-10-31 (cc) <paul4hough@gmail.com>

#include <clue/UserGroup.hpp>
#include <clue/User.hpp>
#include <clue/compare>

#define VALID_VALIDATOR verify
#include <valid/verify.hpp>
#define TEST VVTRUE

#include <sstream>
#include <cstring>

static valid::verify verify("clue::UserGroup");
using namespace clue;


bool
v_UserGroup( void )
{
  gid_t	gid = getgid();
  gid_t egid = getegid();
  gid_t bgid;

  struct group grp;
  struct group egrp;
  struct group bgrp;

  char name[50];
  char ename[50];
  char bname[50];

  struct group * tgrp;

  tgrp = getgrgid( gid );

  strcpy( name, tgrp->gr_name );

  memcpy( &grp, tgrp, sizeof( grp ) );
  grp.gr_name = name;

  tgrp = getgrgid( egid );

  strcpy( ename, tgrp->gr_name );

  memcpy( &egrp, tgrp, sizeof( egrp ) );
  egrp.gr_name = ename;

  tgrp = getgrnam( "bin" );
  TEST( tgrp != 0 );

  strcpy( bname, tgrp->gr_name );
  memcpy( &bgrp, tgrp, sizeof( bgrp ) );
  bgrp.gr_name = bname;
  bgid = bgrp.gr_gid;

  size_t bMembCount = 0;

  for( size_t m = 0; tgrp->gr_mem[m]; m++ )
    bMembCount++;

  {
    // UserGroup( void )
    // getGID( void ) const
    // getName( void ) const
    // getMembers( void ) const

    UserGroup t;

    TEST( t.getGID() == gid );
    TEST( compare( t.getName(), grp.gr_name ) == 0 );
    TEST( t.getMembers().size() == 0 );
  }

  {
    // UserGroup( bool )

    UserGroup t( true );

    TEST( t.getGID() == gid );
    TEST( compare( t.getName(), grp.gr_name ) == 0 );
    TEST( t.getMembers().size() != 0 );
  }

  {
    // UserGroup( gid_t )

    UserGroup t( bgid );

    TEST( t.getGID() == bgid );
    TEST( compare( t.getName(), bgrp.gr_name ) == 0 );
    TEST( t.getMembers().size() == 0 );
  }

  {
    // UserGroup( gid_t, bool )

    UserGroup t( gid, true );

    TEST( t.getGID() == gid );
    TEST( compare( t.getName(), grp.gr_name ) == 0 );
    TEST( t.getMembers().size() != 0 );
  }

  {
    // UserGroup( const char * )

    UserGroup t( bgrp.gr_name );

    TEST( t.getGID() == bgid );
    TEST( compare( t.getName(), bgrp.gr_name ) == 0 );
    TEST( t.getMembers().size() == 0 );
  }

  {
    // UserGroup( const char *, bool )

    UserGroup t( grp.gr_name, true );

    TEST( t.getGID() == gid );
    TEST( compare( t.getName(), grp.gr_name ) == 0);
    TEST( t.getMembers().size() != 0 );
  }

  {
    // UserGroup( struct group * )

    UserGroup t( getgrgid( gid ) );

    TEST( t.getGID() == gid );
    TEST( compare( t.getName(), grp.gr_name ) == 0);
    TEST( t.getMembers().size() == 0 );
  }

  {
    // UserGroup( struct group *, bool )

    UserGroup t( getgrgid( gid ), true );

    TEST( t.getGID() == gid );
    TEST( compare( t.getName(), grp.gr_name ) == 0);
    TEST( t.getMembers().size() != 0 );
  }

  {
    // UserGroup( istream & )

    std::stringstream tStream;

    UserGroup gout( gid );

    gout.write( tStream );

    UserGroup t( tStream );

    TEST( t.getGID() == gid );
    TEST( compare( t.getName(), grp.gr_name ) == 0);
    TEST( t.getMembers().size() == 0 );
  }

  {
    // UserGroup( istream &, bool )
    std::stringstream tStream;

    UserGroup gout( gid );

    tStream << gout;

    UserGroup t( tStream, true );

    TEST( t.getGID() == gid );
    TEST( compare( t.getName(), grp.gr_name ) == 0);
    TEST( t.getMembers().size() == 0 );
  }

  {
    // UserGroup( istream &, bool, bool )
    std::stringstream tStream;

    UserGroup gout( gid );

    tStream << gout;

    UserGroup t( tStream, true, true );

    TEST( t.getGID() == gid );
    TEST( compare( t.getName(), grp.gr_name ) == 0);
    TEST( t.getMembers().size() != 0 );
  }

  {
    // effective( void )

    TEST( UserGroup::effective().getGID() == egid );
  }

  {
    // findMembers( void )
    // getMembers( void ) const
    // isMember( const User & )

    UserGroup t( gid );

    TEST( t.findMembers() > 0 );

    struct group * gent = getgrgid( gid );
    struct group g;

    g.gr_name = strdup( gent->gr_name );

    size_t mCount = 0;
    {
      for( size_t m = 0; gent->gr_mem[m]; m++ )
        {
        // use getpwnam to see if user really exists
        if(getpwnam(gent->gr_mem[m]) != NULL)
          {
	  mCount++;
          }
        }
    }

    g.gr_mem = (char **)malloc( (sizeof( char * ) * mCount) + 1 );

    {
      size_t n = 0;
      for( size_t m = 0; gent->gr_mem[m]; m++ )
	{
          // use getpwnam to see if user really exists
          if(getpwnam(gent->gr_mem[m]) != NULL)
            {
	      g.gr_mem[n++] = strdup( gent->gr_mem[m] );
            }
	}
      g.gr_mem[mCount] = 0;
    }


    TEST( t.getMembers().size() >= mCount );

    {


      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  const User u( g.gr_mem[m] );

	  TEST( t.isMember( u ) );
	}
    }
    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  free( g.gr_mem[m] );
	}
      free( g.gr_mem );
      free( g.gr_name );
    }

  }

  {
    // isMember( const User & ) const

    const UserGroup t( gid, true );

    struct group * gent = getgrgid( gid );
    struct group g;

    g.gr_name = strdup( gent->gr_name );

    size_t mCount = 0;
    {
      for( size_t m = 0; gent->gr_mem[m]; m++ )
        {
        if(getpwnam(gent->gr_mem[m]) != NULL)
          {
  	    mCount++;
          }
        }
    }

    g.gr_mem = (char **)malloc( (sizeof( char * ) * mCount) + 1 );

    {
      size_t n = 0;
      for( size_t m = 0; gent->gr_mem[m]; m++ )
	{
          // use getpwnam to see if user really exists
          if(getpwnam(gent->gr_mem[m]) != NULL)
            {
	      g.gr_mem[n++] = strdup( gent->gr_mem[m] );
            }
	}
      g.gr_mem[mCount] = 0;
    }

    TEST( t.getMembers().size() >= mCount );

    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  const User u( g.gr_mem[m] );

	  TEST( t.isMember( u ) );
	}
    }
    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  free( g.gr_mem[m] );
	}
      free( g.gr_mem );
      free( g.gr_name );
    }
  }

  {
    // isMember( uid_t )

    UserGroup t( gid );

    TEST( t.findMembers() > 0 );

    struct group * gent = getgrgid( gid );
    struct group g;

    g.gr_name = strdup( gent->gr_name );

    size_t mCount = 0;
    {
      for( size_t m = 0; gent->gr_mem[m]; m++ )
        {
        if(getpwnam(gent->gr_mem[m]) != NULL)
          {
	  mCount++;
          }
        }
    }

    g.gr_mem = (char **)malloc( (sizeof( char * ) * mCount) + 1 );

    {
      size_t n = 0;
      for( size_t m = 0; gent->gr_mem[m]; m++ )
	{
          // use getpwnam to see if user really exists
          if(getpwnam(gent->gr_mem[m]) != NULL)
            {
	      g.gr_mem[n++] = strdup( gent->gr_mem[m] );
            }
	}
      g.gr_mem[mCount] = 0;
    }

    TEST( t.getMembers().size() >= mCount );

    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  const User u( g.gr_mem[m] );

	  TEST( t.isMember( u.getUID() ) );
	}
    }
    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  free( g.gr_mem[m] );
	}
      free( g.gr_mem );
      free( g.gr_name );
    }
  }

  {
    // isMember( uid_t ) const

    const UserGroup t( gid, true );


    struct group * gent = getgrgid( gid );
    struct group g;

    g.gr_name = strdup( gent->gr_name );

    size_t mCount = 0;
    {
      for( size_t m = 0; gent->gr_mem[m]; m++ )
        {
        if(getpwnam(gent->gr_mem[m]) != NULL)
          {
	  mCount++;
          }
        }
    }

    g.gr_mem = (char **)malloc( (sizeof( char * ) * mCount) + 1 );

    {
      size_t n = 0;
      for( size_t m = 0; gent->gr_mem[m]; m++ )
	{
          // use getpwnam to see if user really exists
          if(getpwnam(gent->gr_mem[m]) != NULL)
            {
	      g.gr_mem[n++] = strdup( gent->gr_mem[m] );
            }
	}
      g.gr_mem[mCount] = 0;
    }

    TEST( t.getMembers().size() >= mCount );

    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  const User u( g.gr_mem[m] );

	  TEST( t.isMember( u.getUID() ) );
	}
    }
    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  free( g.gr_mem[m] );
	}
      free( g.gr_mem );
      free( g.gr_name );
    }
  }

  {
    // isMember( const char * )

    UserGroup t( gid );

    TEST( t.findMembers() > 0 );

    struct group * gent = getgrgid( gid );
    struct group g;

    g.gr_name = strdup( gent->gr_name );

    size_t mCount = 0;
    {
      for( size_t m = 0; gent->gr_mem[m]; m++ )
        {
        if(getpwnam(gent->gr_mem[m]) != NULL)
          {
	  mCount++;
          }
        }
    }

    g.gr_mem = (char **)malloc( (sizeof( char * ) * mCount) + 1 );

    {
      size_t n = 0;
      for( size_t m = 0; gent->gr_mem[m]; m++ )
	{
          // use getpwnam to see if user really exists
          if(getpwnam(gent->gr_mem[m]) != NULL)
            {
	      g.gr_mem[n++] = strdup( gent->gr_mem[m] );
            }
	}
      g.gr_mem[mCount] = 0;
    }

    TEST( t.getMembers().size() >= mCount );

    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  TEST( t.isMember( g.gr_mem[m] ) );
	}
    }
    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  free( g.gr_mem[m] );
	}
      free( g.gr_mem );
      free( g.gr_name );
    }
  }

  {
    // isMember( const char * ) const

    const UserGroup t( gid, true );

    struct group * gent = getgrgid( gid );
    struct group g;

    g.gr_name = strdup( gent->gr_name );

    size_t mCount = 0;
    {
      for( size_t m = 0; gent->gr_mem[m]; m++ )
        {
        if(getpwnam(gent->gr_mem[m]) != NULL)
          {
	  mCount++;
          }
        }
    }

    g.gr_mem = (char **)malloc( (sizeof( char * ) * mCount) + 1 );

    {
      size_t n = 0;
      for( size_t m = 0; gent->gr_mem[m]; m++ )
	{
          // use getpwnam to see if user really exists
          if(getpwnam(gent->gr_mem[m]) != NULL)
            {
	      g.gr_mem[n++] = strdup( gent->gr_mem[m] );
            }
	}
      g.gr_mem[mCount] = 0;
    }

    TEST( t.getMembers().size() >= mCount );

    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  TEST( t.isMember( g.gr_mem[m] ) );
	}
    }
    {
      for( size_t m = 0; g.gr_mem[m]; m++ )
	{
	  free( g.gr_mem[m] );
	}
      free( g.gr_mem );
      free( g.gr_name );
    }
  }

  {
    // set( gid_t )

    UserGroup t;

    t.set( bgid );

    TEST( t.getGID() == bgid );
    TEST( compare( t.getName(), bgrp.gr_name ) == 0 );
    TEST( t.getMembers().size() == 0 );
  }

  {
    // set( gid_t, bool )

    UserGroup t( bgid );

    t.set( gid, true );

    TEST( t.getGID() == gid );
    TEST( compare( t.getName(), grp.gr_name ) == 0 );
    TEST( t.getMembers().size() != 0 );
  }

  {
    // set( const char * )

    UserGroup t( bgid );

    t.set( grp.gr_name );

    TEST( t.getGID() == gid );
    TEST( compare( t.getName(), grp.gr_name ) == 0 );
    TEST( t.getMembers().size() == 0 );
  }

  {
    // set( const char *, bool )

    UserGroup t( bgid );

    t.set( grp.gr_name, true );

    TEST( t.getGID() == gid );
    TEST( compare( t.getName(), grp.gr_name ) == 0 );
    TEST( t.getMembers().size() != 0 );
  }

  {
    // set( const struct group * )

    UserGroup t( bgid );

    t.set( &grp );

    TEST( t.getGID() == gid );
    TEST( compare( t.getName(), grp.gr_name ) == 0 );
    TEST( t.getMembers().size() == 0 );
  }

  {
    // set( const struct group *, bool )

    UserGroup t( bgid );

    t.set( &grp, true );

    TEST( t.getGID() == gid );
    TEST( compare( t.getName(), grp.gr_name ) == 0 );
    TEST( t.getMembers().size() != 0 );
  }

  {
    // compare( const UserGroup & ) const
    // operator == ( const UserGroup & ) const
    // operator <  ( const UserGroup & ) const
    // operator >  ( const UserGroup & ) const

    const char * l = 0;
    const char * m = 0;

    if( compare( grp.gr_name, bgrp.gr_name ) < 0 )
      {
	l = grp.gr_name;
	m = bgrp.gr_name;
      }
    else
      {
	l = bgrp.gr_name;
	m = grp.gr_name;
      }

    const UserGroup t( l );
    const UserGroup tm( m );

    TEST( t.compare( t ) == 0 );
    TEST( t == t );
    TEST( t.compare( tm ) < 0 );
    TEST( t < tm );
    TEST( tm.compare( t ) > 0 );
    TEST( tm > t );
  }

  {
    // operator const char * ( void ) const
    // operator gid_t ( void ) const;

    const UserGroup t( gid );

    char gn[ 50 ];

    strcpy( gn, t );

    TEST( compare( t.getName(), gn ) == 0 );

    TEST( getgrgid( t )->gr_gid == gid );
  }

  {
    // write( ostream & ) const
    // read( istream & )

    const UserGroup  tw( gid );
    UserGroup	     tr( bgid );

    std::stringstream tStrm;

    std::streampos gpos = tStrm.tellg();
    std::streampos ppos = tStrm.tellp();

    TEST( ppos == 0 );
    TEST( gpos == 0 );

    tw.write( tStrm );
    ppos += (std::streampos) tw.getBinSize();
    TEST( ppos == tStrm.tellp() );

    tr.read( tStrm );
    gpos += (std::streampos) tr.getBinSize();
    TEST( gpos == tStrm.tellg() );
    TEST( tr == tw );
  }

  {
    // toStream( ostream & ) const
    // operator << ( ostream &, const FilePath & )

    std::stringstream tStrm;
    const UserGroup t( gid );

    t.toStream( tStrm );
    tStrm << t;
  }

  {
    // good( void ) const
    // error( void ) const
    // getClassName( void ) const
    // getVersion( void ) const
    // getVersion( bool ) const

    const UserGroup t( gid );

    TEST( t.good() );
    TEST( t.error() != 0 );
  }

  {
    // ::compare( const UserGroup &, const UserGroup & );
    const char * l = 0;
    const char * m = 0;

    if( compare( grp.gr_name, bgrp.gr_name ) < 0 )
      {
	l = grp.gr_name;
	m = bgrp.gr_name;
      }
    else
      {
	l = bgrp.gr_name;
	m = grp.gr_name;
      }

    const UserGroup t( l );
    const UserGroup tm( m );

    TEST( compare( t, t ) == 0 );
    TEST( compare( t, tm ) < 0 );
    TEST( compare( tm, t ) > 0 );
  }
  return( verify.is_valid() );
}
