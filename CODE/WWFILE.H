/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef WWFILE_Hx
#define WWFILE_Hx

#define YEAR(dt)	(((dt & 0xFE000000) >> (9 + 16)) + 1980)
#define MONTH(dt)	 ((dt & 0x01E00000) >> (5 + 16))
#define DAY(dt)	 ((dt & 0x001F0000) >> (0 + 16))
#define HOUR(dt)	 ((dt & 0x0000F800) >> 11)
#define MINUTE(dt) ((dt & 0x000007E0) >> 5)
#define SECOND(dt) ((dt & 0x0000001F) << 1)

#include	<io.h>
#include	<stddef.h>

#ifndef READ
#define READ 1
#endif
#ifndef WRITE
#define WRITE 2
#endif

/*
**	The "bool" integral type was defined by the C++ committee in
**	November of '94. Until the compiler supports this, use the following
**	definition.
*/
#ifndef __BORLANDC__
#ifndef TRUE_FALSE_DEFINED
#define TRUE_FALSE_DEFINED
enum {false=0,true=1};
typedef int bool;
#endif
#endif


class FileClass
{
	public:
		virtual ~FileClass(void) {};
		virtual char const * File_Name(void) const = 0;
		virtual char const * Set_Name(char const *filename) = 0;
		virtual int Create(void) = 0;
		virtual int Delete(void) = 0;
		virtual int Is_Available(int forced=false) = 0;
		virtual int Is_Open(void) const = 0;
		virtual int Open(char const *filename, int rights=READ) = 0;
		virtual int Open(int rights=READ) = 0;
		virtual long Read(void *buffer, long size) = 0;
		virtual long Seek(long pos, int dir=SEEK_CUR) = 0;
		virtual long Size(void) = 0;
		virtual long Write(void const *buffer, long size) = 0;
		virtual void Close(void) = 0;
		virtual unsigned long Get_Date_Time(void) {return(0);}
		virtual bool Set_Date_Time(unsigned long ) {return(false);}
		virtual void Error(int error, int canretry = false, char const * filename=NULL) = 0;

		operator char const * () {return File_Name();};
};

#endif
