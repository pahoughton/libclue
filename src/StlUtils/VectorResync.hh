#ifndef _VectorResync_hh_
#define _VectorResync_hh_
//
// File:        VectorResync.hh
// Project:	StlUtils
// Desc:        
//
//  The VectorResync template function will modify the record indexes for
//  two vectors so that they both point to the same 'key' value. The 'key'
//  is determined by the 'Compare' object. 
//
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     11/04/97 07:36
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

#include <StlUtilsConfig.hh>
#include <DumpInfo.hh>
#include <iostream>

template< class T, class Compare >
inline
bool
VectorResync(
  const T &		a,
  T::size_type	&	aRec,
  const T &		b,
  T::size_type	&	bRec,
  const Compare &	compare
  )
{
  if( compare( a, aRec, b, bRec ) == 0 )
    return( true );

  T::size_type asr = aRec;
  T::size_type bsr = bRec;

  T::size_type	maxRec = min( a.size(), b.size() );

  for( T::size_type end = 1; end < maxRec; ++ end )
    {
      
      for( T::size_type beg = 0; beg < end; ++ beg )
	{
	  if( compare( a, asr + beg, b, bsr + end ) == 0 )
	    {
	      aRec = asr + beg;
	      bRec = bsr + end;
	      return( true );
	    }

	  if( compare( a, asr + end, b, bsr + beg ) == 0 )
	    {
	      aRec = asr + end;
	      bRec = bsr + beg;
	      return( true );
	    }
	}
      
      if( compare( a, asr + end, b, bsr + end ) == 0 )
	{
	  aRec = asr + end;
	  bRec = bsr + end;
	  return( true );
	}
    }
  return( false );
}
  


//
// Detail Documentation
//
// Quick Start: - short example of class usage
//
//  Data Types: - data types defined by this header
//
//  	VectorResync	class
//
//  Constructors:
//
//  	VectorResync( );
//
//  Destructors:
//
//  Public Interface:
//
//	virtual ostream &
//	write( ostream & dest ) const;
//	    write the data for this class in binary form to the ostream.
//
//	virtual istream &
//	read( istream & src );
//	    read the data in binary form from the istream. It is
//	    assumed it stream is correctly posistioned and the data
//	    was written to the istream with 'write( ostream & )'
//
//	virtual ostream &
//	toStream( ostream & dest ) const;
//	    output class as a string to dest (used by operator <<)
//
//	virtual istream &
//	fromStream( istream & src );
//	    Set this class be reading a string representation from
//	    src. Returns src.
//
//  	virtual Bool
//  	good( void ) const;
//  	    Return true if there are no detected errors associated
//  	    with this class, otherwise false.
//
//  	virtual const char *
//  	error( void ) const;
//  	    Return a string description of the state of the class.
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. VectorResync )
//
//  	virtual const char *
//  	getVersion( bool withPrjVer = true ) const;
//  	    Return the version string of this class.
//
//	virtual ostream &
//	dumpInfo( ostream & dest, const char * prefix, bool showVer );
//	    output detail info to dest. Includes instance variable
//	    values, state info & version info.
//
//	static const ClassVersion version
//	    Class and project version information. (see ClassVersion.hh)
//
//  Protected Interface:
//
//  Private Methods:
//
//  Associated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const VectorResync & src );
//
//	istream &
//	operator >> ( istream & src, VectorResync & dest );
//
// Example:
//
// See Also:
//
// Files:
//
// Documented Ver:
//
// Tested Ver:
//
// Revision Log:
//
// $Log$
// Revision 1.1  1998/01/05 13:08:35  houghton
// Initial Version.
//
//
#endif // ! def _VectorResync_hh_ 
