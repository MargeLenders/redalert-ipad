/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef CCFILE_H
#define CCFILE_H

//#include	<wwlib32.h>
#include	<limits.h>
#include	"mixfile.h"
#include	"cdfile.h"
#include	"buff.h"


/*
**	This derived class for file access knows about mixfiles (packed files). It can handle opening
**	a file that is embedded within a mixfile. This is true if the mixfile is cached or resides on
**	disk. It is functionally similar to pakfiles, except much faster and less RAM intensive.
*/
class CCFileClass : public CDFileClass
{
	public:
		CCFileClass(char const * filename);
		CCFileClass(void);
		virtual ~CCFileClass(void) {Position = 0;};

		// Delete should be overloaded here as well. Don't allow deletes of mixfiles.

		bool Is_Resident(void) const {return(Data.Get_Buffer() != NULL);}
		virtual int Is_Available(int forced=false);
		virtual int Is_Open(void) const;
		virtual int Open(char const * filename, int rights=READ) {Set_Name(filename);return Open(rights);};
		virtual int Open(int rights=READ);
		virtual long Read(void * buffer, long size);
		virtual long Seek(long pos, int dir=SEEK_CUR);
		virtual long Size(void);
		virtual long Write(void const * buffer, long size);
		virtual void Close(void);
		virtual unsigned long Get_Date_Time(void);
		virtual bool Set_Date_Time(unsigned long datetime);
		virtual void Error(int error, int canretry = false, char const * filename=NULL);

	private:

		/*
		**	This indicates the file is actually part of a resident image of the mixfile
		**	itself. In this case, the embedded file handle is invalid. All file access actually
		**	gets routed through the cached version of the file. This is a pointer to the start
		**	of the RAM image of the file.
		*/
		::Buffer Data;
//		void * Pointer;

		/*
		**	This is the size of the file if it was embedded in a mixfile. The size must be manually
		**	kept track of because the DOS file size is invalid.
		*/
//		long Length;

		/*
		**	This is the current seek position of the file. It is duplicated here if the file is
		**	part of a mixfile since the DOS seek position is not accurate. This value will
		**	range from zero to the size of the file in bytes.
		*/
		long Position;

		// Force these to never be invoked.
		CCFileClass const & operator = (CCFileClass const & c);
		CCFileClass (CCFileClass const & );
};

#endif
