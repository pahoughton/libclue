#ifndef _SubStr_hh_
#define _SubStr_hh_
//
// File:        SubStr.hh
// Desc:        
//
//  	A 'SubStr' is a section of a 'Str'. Any modifications to
//  	the 'SubStr' modify the 'Str' it is a section of.
//
//  	Detail documentation is at the end of this header file.
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/30/95 14:59
//
// Revision History:
//
// $Log$
// Revision 2.1  1995/11/10 12:41:17  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:54  houghton
// Ports and Version ID changes
//
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <BinStream.hh>
#include <stddef>
#include <iostream>
#else
#include <ClueCfg.hh>
#include <BinStrm.hh>
#include <stddef>
#include <iostream>
#endif

// I'll support string when I can find an implmentation that
// is portable and follows the standard
// #include <string>


#if defined( CLUE_DEBUG )
#define inline
#endif

class Str;

class SubStr : public BinObject
{

public:

  static const size_t npos;
  
  inline SubStr( Str & src, size_t pos = 0, size_t len = NPOS);
  inline SubStr( const Str & src, size_t pos = 0, size_t len = NPOS);

  inline size_t    	size( void ) const; 
  inline size_t    	length( void ) const; 
  inline bool	    	empty( void ) const; 
  
  inline bool	to( bool &   	     dest ) const;
  inline bool	to( int &   	     dest, unsigned short base = 0 ) const; 
  inline bool	to( short & 	     dest, unsigned short base = 0 ) const; 
  inline bool	to( long &  	     dest, unsigned short base = 0 ) const; 
  inline bool	to( float & 	     dest, unsigned short base = 0 ) const; 
  inline bool	to( double & 	     dest, unsigned short base = 0 ) const; 
  inline bool	to( unsigned int &   dest, unsigned short base = 0 ) const; 
  inline bool	to( unsigned short & dest, unsigned short base = 0 ) const; 
  inline bool	to( unsigned long  & dest, unsigned short base = 0 ) const; 
  

  inline bool	    	toBool( void ) const;	    
  inline int	    	toInt( unsigned short base = 0 ) const;	    
  inline long	    	toLong( unsigned short base = 0 ) const;	    
  inline double    	toDouble( unsigned short base = 0 ) const;	    
  inline unsigned int	toUInt( unsigned short base = 0 ) const;	    
  inline unsigned long	toULong( unsigned short base = 0 ) const;	    

  int 	    compare( const Str &    two,
		     size_t         start = 0,
		     size_t         len = NPOS ) const; 
  int	    compare( const SubStr & two,
		     size_t         start = 0,
		     size_t         len = NPOS ) const; 
  int	    compare( const char *   two,
		     size_t         start = 0,
		     size_t         len = NPOS ) const; 
  
  friend int	compare( const char * 	one,
			 const SubStr & two,
			 size_t         len = NPOS ); 
  
  int	    fcompare( const Str &    two,
		      size_t         start = 0,
		      size_t         len = NPOS ) const; 
  int	    fcompare( const SubStr & two,
		      size_t 	     start = 0,
		      size_t 	     len = NPOS ) const; 
  int	    fcompare( const char *   two,
		      size_t 	     start = 0,
		      size_t         len = NPOS ) const; 
  
  friend int	fcompare( const char *    one,
			  const SubStr &  two,
			  size_t          len = NPOS ); 

  inline char &     operator [] ( size_t index ); 
  inline char       operator [] ( size_t index ) const;
  
  inline SubStr &   operator =  ( const SubStr & rhs ); 
  inline SubStr &   operator =  ( const Str & rhs ); 
  inline SubStr &   operator =  ( const char * rhs ); 
  inline SubStr &   operator =  ( char rhs ); 
  
  inline SubStr &   operator += ( const Str & rhs ); 
  inline SubStr &   operator += ( const SubStr & rhs ); 
  inline SubStr &   operator += ( const char * rhs ); 
  inline SubStr &   operator += ( char rhs ); 

  inline bool       operator == ( const SubStr & rhs ) const; 
  inline bool       operator == ( const Str & rhs ) const; 
  inline bool       operator == ( const char * rhs ) const; 
  
  inline bool       operator <  ( const SubStr & rhs ) const; 
  inline bool       operator <  ( const Str & rhs ) const; 
  inline bool       operator <  ( const char * rhs ) const; 

  inline bool       operator != ( const SubStr & rhs ) const; 
  inline bool       operator != ( const Str & rhs ) const; 
  inline bool       operator != ( const char * rhs ) const; 
  
  inline bool       operator >  ( const SubStr & rhs ) const; 
  inline bool       operator >  ( const Str & rhs ) const;
  inline bool       operator >  ( const char * rhs ) const;

  inline bool       operator <= ( const SubStr & rhs ) const; 
  inline bool       operator <= ( const Str & rhs ) const;
  inline bool       operator <= ( const char * rhs ) const;

  inline bool       operator >= ( const SubStr & rhs ) const; 
  inline bool       operator >= ( const Str & rhs ) const;
  inline bool       operator >= ( const char * rhs ) const;
  
  // libClue Common Class Methods

  size_t	    getBinSize( void ) const;
  BinStream &	    write( BinStream & dest ) const;
  BinStream &	    read( BinStream & src );

  ostream &	    write( ostream & dest ) const;
  istream &	    read( istream & src );
  
  inline ostream &  toStream( ostream & dest = cout ) const;

  friend inline ostream &  operator << ( ostream & dest, const SubStr & src ); 
  friend inline istream &  operator >> ( istream & src, SubStr & dest ); 
  
  inline bool	    good( void ) const;
  const char *	    error( void ) const;
  const char *	    getClassName( void ) const;
  const char *	    getVersion( bool withPrjVer = true ) const;
  ostream &	    dumpInfo( ostream &	    dest = cerr,
			      const char *  prefix = "    ",
			      bool	    showVer = true ) const;
  
  static const ClassVersion version;

private:
  
  friend class 	Str;
  
  inline const char * 	strbase( void ) const;
  static Str dummyStr;
  
  Str &	    	str;
  const Str &   constStr;
  size_t    	pos;
  size_t    	len;

};

#if !defined( inline )
#include <SubStr.ii>
#else
#undef inline

// These are the global functions that are defined in the .ii
// file. They are declared here so their prototypes will
// be available when CLUE_DEBUG is defined.

int
compare( const SubStr & one,
	 const char *   two,
	 size_t         len = SubStr::npos ); 
  
int
fcompare( const SubStr & one,
	  const char *   two,
	  size_t         len = SubStr::npos ); 

Str
operator + ( const SubStr & lhs, const Str & rhs );

Str
operator + ( const SubStr & lhs, const SubStr & rhs );

Str
operator + ( const SubStr & lhs, const char * rhs );

Str
operator + ( const char * lhs, const SubStr & rhs );

bool
operator == ( const char * lhs, const SubStr & rhs );

bool
operator != ( const char * lhs, const SubStr & rhs );

bool
operator <  ( const char * lhs, const SubStr & rhs );

bool
operator >  ( const char * lhs, const SubStr & rhs );

bool
operator <= ( const char * lhs, const SubStr & rhs );

bool
operator >= ( const char * lhs, const SubStr & rhs );

bool	    	StringToBool( const SubStr & str );
int 	    	StringToInt( const SubStr & str, unsigned short base = 0 );
long	    	StringToLong( const SubStr & str, unsigned short base = 0 );
double	    	StringToDouble( const SubStr & str, unsigned short base = 0 );
unsigned int 	StringToUInt( const SubStr & str, unsigned short base = 0 );
unsigned long	StringToULong( const SubStr & str, unsigned short base = 0 );

#endif  

//  Quick Start: - short example of class usage
//
//  Data Types: - data types defined by this header
//
//  	SubStr	class
//
//  Constructors:
//
//  	SubStr( );
//
//  Destructors:
//
//  Public Interface:
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. SubStr )
//
//  	virtual Bool
//  	good( void ) const;
//  	    Returns true if there are no detected errors associated
//  	    with this class, otherwise FALSE.
//
//  	virtual const char *
//  	error( void ) const
//  	    Returns as string description of the state of the class.
//
//  Protected Interface:
//
//  Private Methods:
//
//  Other Associated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const SubStr & obj );
//

#endif // ! def _SubStr_hh_ 
