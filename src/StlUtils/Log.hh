#ifndef _Log_hh_
#define _Log_hh_
//
// File:        Log.hh
// Desc:        
//              
//
// Author:      Paul Houghton x2309 - (houghton@shoe)
// Created:     03/14/94 10:49
//
// Revision History:
//
// $Log$
// Revision 1.7  1995/11/05 15:28:37  houghton
// Revised
//
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <LogBuf.hh>
#include <iostream>
#include <iomanip>
#include <fstream>
#else
#include <ClueCfg.hh>
#include <LogBuf.hh>
#include <iostream>
#include <iomanip>
#include <fstream>
#endif




#define WHERE  __FILE__ << ':' << __LINE__ 

#define LogIf( lg, lvl ) if( (lg).willOutput( lvl ) ) ((lg)( lvl ))

#if defined( CLUE_DEBUG )
#define inline
#endif

class Log : public ostream
{

public:

  inline Log( ostream & 	outStream = cout,
	      LogLevel::Level 	outLevel = LogLevel::ERROR,
	      bool		stampLevel = true,
	      bool		stampTime = true );

  inline Log( ostream & 	outStream,
	      const char *      outLevel,
	      bool		stampLevel = true,
	      bool		stampTime = true ); 
  
  inline Log( const char * 	fileName,
	      LogLevel::Level 	outLevel = LogLevel::ERROR,
	      bool		stampLevel = true,
	      bool		stampTime = true,
	      ios::open_mode	mode = ios::app,
	      int		prot = filebuf::openprot,
	      size_t		maxSize = 0,
	      size_t		trimSize = 0 );
	      
  inline Log( const char * 	fileName,
	      const char *	outLevel,
	      bool		stampLevel = true,
	      bool		stampTime = true,
	      ios::open_mode	mode = ios::app,
	      int		prot = filebuf::openprot,
	      size_t		maxSize = 0,
	      size_t		trimSize = 0 );

  inline ~Log( void );
  
  inline void 	    	    tee( ostream & teeStream = cerr );
  inline size_t		    trim( size_t maxSize = 0 );
  inline size_t		    setMaxSize( size_t maxSize );
  inline size_t		    setTrimSize( size_t trimSize );
  
  Log &		    level( LogLevel::Level curren = LogLevel::ERROR );
  inline Log &	    operator () ( void );
  inline Log &	    operator () ( LogLevel::Level current );

  Log &		    level( const char * current );  
  inline Log &      operator () ( const char * current );
  
  inline void		    on( LogLevel::Level output );
  inline void		    off( LogLevel::Level output );
  
  inline LogLevel::Level    getCurrent( void  ) const;
  inline LogLevel::Level    getOutput( void ) const;

  inline bool	    	    willOutput( LogLevel::Level outLevel ) const;
  

  inline void		    setFileName( const char * f, int mode = ios::app );
  inline void		    open( const char * f, int mode = ios::app );
  inline void		    close( void );
  
  inline LogLevel::Level    setOutputLevel( const char * output );
  inline LogLevel::Level    setOutputLevel( LogLevel::Level output );

  inline bool		    setLevelStamp( bool stamp );
  inline bool		    setTimeStamp( bool stamp );

  inline LogBuf *	    rdbuf( void );
  inline const LogBuf *	    rdbuf( void ) const;

  virtual bool 		good( void ) const;
  virtual const char *	error( void ) const;
  virtual const char *	getClassName( void ) const;
  virtual const char *	getVersion( bool withPrjVer = true ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;
  
  static const ClassVersion version;
  
protected:

private:

  Log( const Log & copyFrom );
  Log & operator=( const Log & assignFrom );

  bool		timeStamp;
  bool		levelStamp;
  
};

#ifndef inline
#include <Log.ii>
#else
#undef inline
#endif


#endif // ! def _Log_hh_ 
