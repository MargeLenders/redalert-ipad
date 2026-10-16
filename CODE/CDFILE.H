/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef CDFILE_H
#define CDFILE_H

#include	<dos.h>
#include	"bfiofile.h"

/*
**	This class is derived from the BufferIOFileClass. This class adds the functionality of searching
**	across multiple directories or drives. It is designed for the typical case of a CD-ROM game
**	were some data exists in the current directory (hard drive) and the rest exists on the CD-ROM.
**	Searching for the file occurs by first examining the current directory. If the file does not
**	exist there, then all the paths available are examined in turn until the file can be found.
**	For opening files to write, only the current directory is examined. The directory search order
**	is controlled by the path list as submitted to Set_Search_Drives(). The format of the path
**	string is the same as the DOS path string.
*/
class CDFileClass : public BufferIOFileClass
{
	public:
		CDFileClass(char const *filename);
		CDFileClass(void);
		virtual ~CDFileClass(void) {};

		virtual char const * Set_Name(char const *filename);
		virtual int Open(char const *filename, int rights=READ);
		virtual int Open(int rights=READ);

		void Searching(int on) {IsDisabled = !on;};

		static bool Is_There_Search_Drives(void) {return(First != NULL);};
		static int Set_Search_Drives(char * pathlist);
		static void Add_Search_Drive(char *path);
		static void Clear_Search_Drives(void);
		static void Refresh_Search_Drives(void);
		static void Set_CD_Drive(int drive);
		static int  Get_CD_Drive(void) {return(CurrentCDDrive);};
		static int  Get_Last_CD_Drive(void) {return(LastCDDrive);};

	private:

		/*
		**	Is multi-drive searching disabled for this file object?
		*/
		unsigned IsDisabled:1;

		/*
		**	This is the control record for each of the drives specified in the search
		**	path. There can be many such search paths available.
		*/
		typedef struct {
			void * Next;		// Pointer to next search record.
			char const * Path;			// Pointer to path string.
		} SearchDriveType;

		/*
		**	This points to the first path record.
		*/
		static SearchDriveType * First;
		/*
		** This is a copy of the unparsed search path list
		*/
		static char RawPath[512];

		/*
		** The drive letter of the current cd drive
		*/
		static int CurrentCDDrive;

		/*
		** The drive letter of the last used CD drive
		*/
		static int LastCDDrive;
};

#endif

