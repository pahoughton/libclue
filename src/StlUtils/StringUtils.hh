#ifndef _StringUtils_hh_
#define _StringUtils_hh_
//
// File:        StringUtils.hh
// Project:	Clue
// Desc:        
//
//  This is a collection of char string utility functions. They
//  all operate on char * or const char * objects.
//
//  Many of these function use 'NPOS' as a default argument for
//  the string's length. When this value is passed, the string
//  is search for a null terminator (i.e. 0).
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/02/95 06:32
//
// Revision History: (See end of file for Revision Log)
//
// $Id$ 
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <cstring>
#else
#include <ClueCfg.hh>
#include <cstring>
#endif

char *
CLUE_FUNCT_T
StripWhite( char *  	    buffer,
	    const char *    white = " \n\t\r\v\f",
	    size_t          bufSize = NPOS );

const char *
CLUE_FUNCT_T
StringSearch( const char *  haystack,
	      size_t        hayLen,
	      const char *  needle,
	      size_t        needleLen );

const char *
CLUE_FUNCT_T
StringReverseSearch( const char *  haystack,
		     size_t        hayLen,
		     const char *  needle,
		     size_t        needleLen );

const char * 
CLUE_FUNCT_T
StringCaseSearch( const char *  haystack,
		  size_t        hayLen,
		  const char *  needle,
		  size_t        needleLen );

const char * 
CLUE_FUNCT_T
StringCaseReverseSearch( const char *  haystack,
			 size_t        hayLen,
			 const char *  needle,
			 size_t        needleLen );

int
CLUE_FUNCT_T
StringCaseCompare( const char * one, const char * two );

int
CLUE_FUNCT_T
StringCaseCompare( const char * one, const char * two, size_t len );

int
CLUE_FUNCT_T
StringCaseCompare( const char * one, size_t lenOne,
		   const char * two, size_t lenTwo );


char *
CLUE_FUNCT_T
StringLower( char * str, size_t len = NPOS );

char *
CLUE_FUNCT_T
StringUpper( char * str, size_t len = NPOS );

char *
CLUE_FUNCT_T
StringCapitalize( char * str, size_t len = NPOS );


bool
CLUE_FUNCT_T
StringTo( bool & 	    	dest,
	  const char *  	str,
	  size_t 	    	len = NPOS );

bool
CLUE_FUNCT_T
StringTo( int &     	    dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = NPOS );

bool
CLUE_FUNCT_T
StringTo( short &     	    dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = NPOS );

bool
CLUE_FUNCT_T
StringTo( long &     	    dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = NPOS );

bool
CLUE_FUNCT_T
StringTo( float &     	    dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = NPOS );

bool
CLUE_FUNCT_T
StringTo( double &     	    dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = NPOS );

bool
CLUE_FUNCT_T
StringTo( unsigned int &    dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = NPOS );

bool
CLUE_FUNCT_T
StringTo( unsigned short &  dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = NPOS );

bool
CLUE_FUNCT_T
StringTo( unsigned long &   dest,
	  const char * 	    str,
	  unsigned short    base = 0,
	  size_t    	    len = NPOS );

bool
CLUE_FUNCT_T
StringToBool( const char * str, size_t len = NPOS );

int
CLUE_FUNCT_T
StringToInt( const char * str, unsigned short base = 0, size_t len = NPOS );

short
CLUE_FUNCT_T
StringToShort( const char * str, unsigned short base = 0, size_t len = NPOS );

long
CLUE_FUNCT_T
StringToLong( const char * str, unsigned short base = 0, size_t len = NPOS );

float
CLUE_FUNCT_T
StringToFloat( const char * str, unsigned short base = 0, size_t len = NPOS );

double
CLUE_FUNCT_T
StringToDouble( const char * str, unsigned short base = 0, size_t len = NPOS );

unsigned int
CLUE_FUNCT_T
StringToUInt( const char * str, unsigned short base = 0, size_t len = NPOS );

unsigned short
CLUE_FUNCT_T
StringToUShort( const char * str, unsigned short base = 0, size_t len = NPOS );

unsigned long
CLUE_FUNCT_T
StringToULong( const char * str, unsigned short base = 0, size_t len = NPOS );


const char *
CLUE_FUNCT_T
basename( const char * fn );

char *
CLUE_FUNCT_T
basename( char * fn );


#if !defined( CLUE_SHORT_FN )
#include <StringUtils.ii>
#else
#include <StrUtil.ii>
#endif

//
// Detail Documentation:
//
//  Functions:
//
//	char *
//	StripWhite( char *  	    buffer,
//		    const char *    white = " \n\t\r\v\f",
//		    size_t          bufSize = NPOS );
//	    Remove leading and trailing 'white' characters from
//	    'buffer' and return buffer. If bufSize == 0, the string
//	    is NOT modified.
//
//	const char *
//	StringSearch( const char *  haystack,
//		      size_t        hayLen,
//		      const char *  needle,
//		      size_t        needleLen );
//	    Search the string 'haystack' for the string 'needle'. If
//	    'needle' is found in 'haystack' a pointer to the first char
//	    of 'needle' in 'haystack' is returned. If 'needle' is not found,
//	    a 0 is returned. Use NPOS for the len parameters if the
//	    corresponding string is null (0) terminated.
//	
//	const char *
//	StringReverseSearch( const char *  haystack,
//			     size_t        hayLen,
//			     const char *  needle,
//			     size_t        needleLen );
//	    Search the string 'haystack' for the string 'needle' starting
//	    from the end of 'haystack'. If 'needle' is found in 'haystack'
//	    a pointer to the first char of 'needle' in 'haystack' is
//	    returned. If 'needle' is not found, a 0 is returned.
//	    Use NPOS for the len parameters if the corresponding string
//	    is null (0) terminated.
//	
//	
//	const char * 
//	StringCaseSearch( const char *  haystack,
//			  size_t        hayLen,
//			  const char *  needle,
//			  size_t        needleLen );
//	    Search the string 'haystack' for the string 'needle' ignoring
//	    case. If 'needle' is found in 'haystack' a pointer to the first
//	    char of 'needle' in 'haystack' is returned. If 'needle' is not
//	    found, a 0 is returned. Use NPOS for the len parameters if the
//	    corresponding string is null (0) terminated.
//	
//	
//	const char * 
//	StringCaseReverseSearch( const char *  haystack,
//				 size_t        hayLen,
//				 const char *  needle,
//				 size_t        needleLen );
//	    Search the string 'haystack' for the string 'needle' starting
//	    from the end of 'haystack' and ignoring case. If 'needle' is
//	    found in 'haystack' a pointer to the first char of 'needle'
//	    in 'haystack' is returned. If 'needle' is not found, a 0 is
//	    returned. Use NPOS for the len parameters if the corresponding
//	    string is null (0) terminated.
//	
//	int
//	StringCaseCompare( const char * one, const char * two );
//	    Compare two strings ignoring case. return 0 if one == two,
//	    return < 0 if one < two, and return > 0 if one > two.
//	
//	int
//	StringCaseCompare( const char * one, const char * two, size_t len );
//	    Compare the first 'len' chars of two strings ignoring case.
//	    return 0 if one == two, return < 0 if one < two, and
//          return > 0 if one > two.
//	
//	int
//	StringCaseCompare( const char * one, size_t lenOne,
//			   const char * two, size_t lenTwo );
//	    Compare the two strings ignoring case. The first
//	    min( lenOne, lenTwo) char are check first if they are
//	    not the same, the difference is return. If they are the
//	    same, the differance of lenOne and lenTwo is returnd.
//	
//	char *
//	StringLower( char * str, size_t len = NPOS );
//	    Convert all upper case characters (A-Z) to lower case (a-z).
//	    Returns str.
//
//	
//	char *
//	StringUpper( char * str, size_t len = NPOS );
//	    Convert all lower case characters (a-z) to upper case (A-Z).
//	    Returns str.
//
//	char *
//	StringCapitalize( char * str, size_t len = NPOS );
//	    Convert the first lower case alpha (a-z) char of
//	    every word to upper case and convert every other
//	    character in every word to lower case. Returns str.
//	
//	bool
//	StringTo( bool & 	    	dest,
//		  const char *  	str,
//		  size_t 	    	len = NPOS );
//	    Set dest by converting str to a bool value. If str is
//	    'yes', 'true', 'on', 't', 'y' or a non zero number, dest
//	    will be set to true (case is ignored). Else if str is 'no',
//	    'false', 'off', 'f', 'n', ' ' or '0', dest will be
//	    set to false. Returns true if dest was set or false if
//	    str could not be converted.
//
//	bool
//	StringTo( int &     	    dest,
//		  const char * 	    str,
//		  unsigned short    base = 0,
//		  size_t    	    len = NPOS );
//	    Set dest by converting str to a numeric value. base is
//	    the base to use for the conversion (i.e. 8 = for oct,
//	    10 for dec, 16 for hex), it can be any value between
//	    2 and 36 or 0. If base is zero the beginning of str is
//	    used to determine base. If it is 0x or 0X the base is 16.
//	    If it is 0 the base is 8. Otherwise the base is 10.
//	    Returns true if dest was set or false if str could
//	    not be converted.
//	
//	bool
//	StringTo( short &     	    dest,
//		  const char * 	    str,
//		  unsigned short    base = 0,
//		  size_t    	    len = NPOS );
//	    Set dest by converting str to a numeric value. base is
//	    the base to use for the conversion (i.e. 8 = for oct,
//	    10 for dec, 16 for hex), it can be any value between
//	    2 and 36 or 0. If base is zero the beginning of str is
//	    used to determine base. If it is 0x or 0X the base is 16.
//	    If it is 0 the base is 8. Otherwise the base is 10.
//	    Returns true if dest was set or false if str could
//	    not be converted.
//	
//	bool
//	StringTo( long &     	    dest,
//		  const char * 	    str,
//		  unsigned short    base = 0,
//		  size_t    	    len = NPOS );
//	    Set dest by converting str to a numeric value. base is
//	    the base to use for the conversion (i.e. 8 = for oct,
//	    10 for dec, 16 for hex), it can be any value between
//	    2 and 36 or 0. If base is zero the beginning of str is
//	    used to determine base. If it is 0x or 0X the base is 16.
//	    If it is 0 the base is 8. Otherwise the base is 10.
//	    Returns true if dest was set or false if str could
//	    not be converted.
//	
//	bool
//	StringTo( float &     	    dest,
//		  const char * 	    str,
//		  unsigned short    base = 0,
//		  size_t    	    len = NPOS );
//	    Set dest by converting str to a numeric value. base is
//	    the base to use for the conversion (i.e. 8 = for oct,
//	    10 for dec, 16 for hex), it can be any value between
//	    2 and 36 or 0. If base is zero the beginning of str is
//	    used to determine base. If it is 0x or 0X the base is 16.
//	    If it is 0 the base is 8. Otherwise the base is 10.
//	    Returns true if dest was set or false if str could
//	    not be converted.
//	
//	bool
//	StringTo( double &     	    dest,
//		  const char * 	    str,
//		  unsigned short    base = 0,
//		  size_t    	    len = NPOS );
//	    Set dest by converting str to a numeric value. base is
//	    the base to use for the conversion (i.e. 8 = for oct,
//	    10 for dec, 16 for hex), it can be any value between
//	    2 and 36 or 0. If base is zero the beginning of str is
//	    used to determine base. If it is 0x or 0X the base is 16.
//	    If it is 0 the base is 8. Otherwise the base is 10.
//	    Returns true if dest was set or false if str could
//	    not be converted.
//	
//	bool
//	StringTo( unsigned int &    dest,
//		  const char * 	    str,
//		  unsigned short    base = 0,
//		  size_t    	    len = NPOS );
//	    Set dest by converting str to a numeric value. base is
//	    the base to use for the conversion (i.e. 8 = for oct,
//	    10 for dec, 16 for hex), it can be any value between
//	    2 and 36 or 0. If base is zero the beginning of str is
//	    used to determine base. If it is 0x or 0X the base is 16.
//	    If it is 0 the base is 8. Otherwise the base is 10.
//	    Returns true if dest was set or false if str could
//	    not be converted.
//	
//	bool
//	StringTo( unsigned short &  dest,
//		  const char * 	    str,
//		  unsigned short    base = 0,
//		  size_t    	    len = NPOS );
//	    Set dest by converting str to a numeric value. base is
//	    the base to use for the conversion (i.e. 8 = for oct,
//	    10 for dec, 16 for hex), it can be any value between
//	    2 and 36 or 0. If base is zero the beginning of str is
//	    used to determine base. If it is 0x or 0X the base is 16.
//	    If it is 0 the base is 8. Otherwise the base is 10.
//	    Returns true if dest was set or false if str could
//	    not be converted.
//	
//	bool
//	StringTo( unsigned long &   dest,
//		  const char * 	    str,
//		  unsigned short    base = 0,
//		  size_t    	    len = NPOS );
//	    Set dest by converting str to a numeric value. base is
//	    the base to use for the conversion (i.e. 8 = for oct,
//	    10 for dec, 16 for hex), it can be any value between
//	    2 and 36 or 0. If base is zero the beginning of str is
//	    used to determine base. If it is 0x or 0X the base is 16.
//	    If it is 0 the base is 8. Otherwise the base is 10.
//	    Returns true if dest was set or false if str could
//	    not be converted.
//	
//	bool
//	StringToBool( const char * str, size_t len = NPOS );
//	    Uses StringTo to convert the str and returns
//	    the value. If StringTo returned false, 'false' is returned.
//	
//	int
//	StringToInt( const char *   str,
//		     unsigned short base = 0,
//		     size_t	    len = NPOS );
//	    Uses StringTo to convert the str and returns the
//	    value. If StringTo returned false, 0 is returned.
//	
//	short
//	StringToShort( const char *	str,
//		       unsigned short	base = 0,
//		       size_t		len = NPOS );
//	    Uses StringTo to convert the str and returns the
//	    value. If StringTo returned false, 0 is returned.
//	
//	long
//	StringToLong( const char *	str,
//		      unsigned short	base = 0,
//		      size_t		len = NPOS );
//	    Uses StringTo to convert the str and returns the
//	    value. If StringTo returned false, 0 is returned.
//	
//	float
//	StringToFloat( const char *	str,
//		       unsigned short	base = 0,
//		       size_t		len = NPOS );
//	    Uses StringTo to convert the str and returns the
//	    value. If StringTo returned false, 0 is returned.
//	
//	double
//	StringToDouble( const char *	str,
//			unsigned short  base = 0,
//			size_t          len = NPOS );
//	    Uses StringTo to convert the str and returns the
//	    value. If StringTo returned false, 0 is returned.
//	
//	unsigned int
//	StringToUInt( const char *	str,
//		      unsigned short	base = 0,
//		      size_t		len = NPOS );
//	    Uses StringTo to convert the str and returns the
//	    value. If StringTo returned false, 0 is returned.
//	
//	unsigned short
//	StringToUShort( const char *	str,
//			unsigned short  base = 0,
//			size_t		len = NPOS );
//	    Uses StringTo to convert the str and returns the
//	    value. If StringTo returned false, 0 is returned.
//	
//	unsigned long
//	StringToULong( const char *	str,
//		       unsigned short	base = 0,
//		       size_t		len = NPOS );
//	    Uses StringTo to convert the str and returns the
//	    value. If StringTo returned false, 0 is returned.
//	
//	const char *
//	basename( const char * fn );
//	    Returns a pointer to the filename from part of 'fn'
//	    without the directory part.
//	
//	char *
//	basename( char * fn );
//	    Returns a pointer to the filename from part of 'fn'
//	    without the directory part.
//
//	inline
//	char *
//	SafeStrcpy( char * dest, const char * src, size_t size )
//	    Copy 'size' chars of 'src' into dest and
//	    set dest[size-1] to 0. Returns dest.
//
//	inline
//	int
//	CharToInt( char c )
//	    Return 'c' as a numeric value. If 'c' is not 0-9,
//	    Return -1.
//
//	inline
//	bool
//	CharIsBaseDigit( char c, unsigned short base )
//	    Return true if 'c' is a valid digit of 'base'. Otherwise
//	    return false.
//
//  Files:
//
//	StringUtils.hh, StringUtils.ii, libClue.a
//
//  Documented Ver: 2.4
//  Tested Ver: 2.4
//
// Revision Log:
//
// $Log$
// Revision 2.4  1996/11/04 14:33:07  houghton
// Restructure header comments layout.
// Updated and verified header comment documentation.
// Changed default len to be NPOS instead of 0.
//
// Revision 2.3  1996/07/09 11:34:47  houghton
// Bug-Fix: Change to StringToBool to StringTo.
//
// Revision 2.2  1996/04/27 13:09:35  houghton
// Cleanup includes.
//
// Revision 2.1  1995/11/10 12:41:15  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:52  houghton
// Ports and Version ID changes
//
//

#endif // ! def _StringUtils_hh_ 
