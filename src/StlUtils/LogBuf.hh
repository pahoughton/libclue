#ifndef _LogBuf_hh_
#define _LogBuf_hh_
//
// File:        LogBuf.hh
// Desc:        
//              
//
// Author:      Paul Houghton x2309 - (houghton@shoe.wiltel.com)
// Created:     01/29/95 12:32
//
// Revision History:
//
// 
// $Log$
// Revision 1.4  1995/11/05 15:28:39  houghton
// Revised
//
//

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <LogLevel.hh>
#include <FilePath.hh>
#include <iostream>
#include <fstream>
#else
#include <ClueCfg.hh>
#include <LogLvl.hh>
#include <FilePath.hh>
#include <iostream>
#include <fstream>
#endif


#if defined( CLUE_DEBUG )
#define inline
#endif

class LogBuf : public streambuf
{
  
public:
  
  inline LogBuf( LogLevel::Level   outLevel,
		 streambuf * 	   outStream );

  inline LogBuf( const char * 	outLevel,
		 streambuf * 	outStream );

  inline LogBuf( const char *	    fileName,
		 LogLevel::Level    outLevel = LogLevel::ERROR, 
		 ios::open_mode	    mode = ios::app,
		 int		    prot = filebuf::openprot,
		 size_t		    maxSize = 0,
		 size_t		    trimSize = 0 );
  
  inline LogBuf( const char *	    fileName,
		 const char *	    outLevel,
		 ios::open_mode	    mode = ios::app,
		 int		    prot = filebuf::openprot,
		 size_t		    maxSize = 0,

		 size_t		    trimSize = 0 );
  
  virtual ~LogBuf( void );

  inline bool		willOutput( LogLevel::Level outputLevel ) const;

  
  inline streambuf *	tee( streambuf * teeStreambuf );
  filebuf *		open( const char *	name,
			      ios::open_mode    mode,
			      int	        prot = filebuf::openprot,
			      size_t	        maxSize = 0,
			      size_t	        trimSize = 0 );
  
  void			close (void);

  size_t		trim( size_t maxSize = 0 );
  inline size_t	        setMaxSize( size_t maxSize );
  inline size_t		setTrimSize( size_t trimSize );
  
  inline bool		isFile( void ) const;
  
  inline LogLevel &	   level( void );
  inline const LogLevel &  level( void ) const;

  virtual int	    overflow(int=EOF);
  virtual int	    underflow();
  virtual int	    sync() ;

  virtual const char *  getClassName( void ) const;
  virtual const char *	getVersion( bool withPrjVer = true ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;
  
  static const ClassVersion version;
  
protected:
  
private:

  void initLogBuffer( void );
  void initbuf( streambuf * outStream );
  void initbuf( const char * fn,
		ios::open_mode mode,
		int prot,
		size_t m,
		size_t t );
  

  filebuf *	openLog( void );
  size_t	trimLog( size_t curSize, size_t maxLogSize );
  void		closeLog( void );
  
  FilePath	    logFileName;
  size_t	    maxSize;
  size_t	    trimSize;
  ios::open_mode    openMode;
  int		    openProt;
  bool		    streamIsFile;
  
  char *    	buffer;
  streambuf *	stream;
  streambuf * 	teeStream;
  
  LogLevel 	logLevel;
  
};

#if !defined( inline )
#include <LogBuf.ii>
#else
#undef inline
#endif

#endif // ! def _LogBuf_hh_ 
