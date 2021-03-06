#ifndef _SubThread_hh_
#define _SubThread_hh_
//
// File:        SubThread.hh
// Desc:        
//
//
//
//  Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul4hough@gmail.com)
// Created:     07/16/96 06:39
//
// Revision History:
//
// $Log$
// Revision 6.2  2011/12/30 23:57:54  paul
// First go at Mac gcc Port
//
// Revision 6.1  2003/08/09 11:22:54  houghton
// Changed to version 6
//
// Revision 5.1  2000/05/25 10:33:34  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:15:09  houghton
// Changed to Version 4
//
// Revision 3.2  1997/09/17 11:10:24  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.1  1996/11/14 01:28:08  houghton
// Changed to Release 3
//
// Revision 1.1  1996/07/16 13:54:08  houghton
// *** empty log message ***
//
//

#include <StlUtilsConfig.hh>
#include <ThreadBase.hh>

class SubThread : public ThreadBase
{

public:

  SubThread( bool detach = false ) : ThreadBase( detach ) {};

  virtual ~SubThread( void );

protected:

  bool	main( void );
  
private:

  SubThread( const SubThread & from );
  SubThread & operator =( const SubThread & from );

};



//
// Detail Documentation
//
//  Data Types: - data types defined by this header
//
//  	SubThread	class
//
//  Constructors:
//
//  	SubThread( );
//
//  Destructors:
//
//  Public Interface:
//
//  	virtual const char *
//  	getClassName( void ) const;
//  	    Return the name of this class (i.e. SubThread )
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
//  	operator <<( ostream & dest, const SubThread & obj );

#endif // ! def _SubThread_hh_ 

