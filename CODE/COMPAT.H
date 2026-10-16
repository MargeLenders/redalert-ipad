/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef COMPAT_H
#define COMPAT_H

#include <stdint.h>


#define	BuffType		BufferClass
//#define movmem(a,b,c) memmove(b,a,c)
#define ShapeBufferSize	_ShapeBufferSize

/*=========================================================================*/
/* Define some equates for the different graphic routines we will install	*/
/*		later.																					*/
/*=========================================================================*/
#define HIDBUFF	  ((void *)(0xA0000))
#define Size_Of_Region(a, b) ((a)*(b))

/*=========================================================================*/
/* Define some Graphic Routines which will only be fixed by these defines	*/
/*=========================================================================*/
#define Set_Font_Palette(a) 		Set_Font_Palette_Range(a, 0, 15)

/*
**	These are the Open_File, Read_File, and Seek_File constants.
*/
#define READ						1	// Read access.
#define WRITE						2	// Write access.

#ifndef SEEK_SET
#define SEEK_SET					0	// Seek from start of file.
#define SEEK_CUR					1	// Seek relative from current location.
#define SEEK_END					2	// Seek from end of file.
#endif

#define ERROR_WINDOW 			1
#define ErrorWindow 			1


//extern unsigned char *Palette;
extern unsigned char MDisabled;			// Is mouse disabled?
extern WORD Hard_Error_Occured;

/*
**	This is the menu control structures.
*/
typedef enum MenuIndexType {
	MENUX,
	MENUY,
	ITEMWIDTH,
	ITEMSHIGH,
	MSELECTED,
	NORMCOL,
	HILITE,
	MENUPADDING=0x1000
} MenuIndexType;


#ifdef NEVER
#define BITSPERBYTE 8
#define MAXSHORT    0x7FFF
#define HIBITS      0x8000
#define MAXLONG     0x7FFFFFFFL
#define HIBITL      0x80000000

#define MAXINT      MAXLONG
#define HIBITI      HIBITL

#define DMAXEXP     308
#define FMAXEXP     38
#define DMINEXP     -307
#define FMINEXP     -37

#define MAXDOUBLE   1.797693E+308
#define MAXFLOAT    3.37E+38F
#define MINDOUBLE   2.225074E-308
#define MINFLOAT    8.43E-37F

#define DSIGNIF     53
#define FSIGNIF     24

#define DMAXPOWTWO  0x3FF
#define FMAXPOWTWO  0x7F
#define DEXPLEN     11
#define FEXPLEN     8
#define EXPBASE     2
#define IEEE        1
#define LENBASE     1
#define HIDDENBIT   1
#define LN_MAXDOUBLE    7.0978E+2
#define LN_MINDOUBLE    -7.0840E+2
#endif

/* These defines handle the various names given to the same color. */
#define	DKGREEN	GREEN
#define	DKBLUE	BLUE
#define	GRAY		GREY
#define	DKGREY	GREY
#define	DKGRAY	GREY
#define	LTGRAY	LTGREY


class IconsetClass;
#ifndef WIN32
typedef struct {
	short	Width;			// Width of icons (pixels).
	short	Height;			// Height of icons (pixels).
	short	Count;			// Number of (logical) icons in this set.
	short	Allocated;		// Was this iconset allocated?
	short MapWidth;		// Width of map (in icons).
	short MapHeight;		// Height of map (in icons).
	int32_t	Size;				// Size of entire iconset memory block.
	int32_t	Icons;			// Offset from buffer start to icon data.
//	unsigned char * Icons;	// Offset from buffer start to icon data.
	int32_t	Palettes;		// Offset from buffer start to palette data.
	int32_t	Remaps;			// Offset from buffer start to remap index data.
	int32_t	TransFlag;		// Offset for transparency flag table.
	int32_t	ColorMap;		// Offset for color control value table.
	int32_t	Map;				// Icon map offset (if present).
//	unsigned char * Map;				// Icon map offset (if present).
} IControl_Type;
#endif

inline int Get_IconSet_MapWidth(void const * data)
{
	if (data) {
		return(((IControl_Type *)data)->MapWidth);
	}
	return(0);
}

inline int Get_IconSet_MapHeight(void const * data)
{
	if (data) {
		return(((IControl_Type *)data)->MapHeight);
	}
	return(0);
}

inline unsigned char const * Get_IconSet_ControlMap(void const * data)
{
	if (data) {
		return((unsigned char const *)((char *)data + ((IControl_Type *)data)->ColorMap));
	}
	return(0);
}

class IconsetClass : protected IControl_Type
{
	public:
		/*
		**	Query functions.
		*/
		int Map_Width(void) const {return(MapWidth);};
		int Map_Height(void) const {return(MapHeight);};
		unsigned char * Control_Map(void) {return((unsigned char *)this + ColorMap);};
		unsigned char const * Control_Map(void) const {return((unsigned char const *)this + ColorMap);};
		int Icon_Count(void) const {return(Count);};
		int Pixel_Width(void) const {return(Width);};
		int Pixel_Height(void) const {return(Height);};
		int Total_Size(void) const {return(Size);};
		unsigned char const * Palette_Data(void) const {return((unsigned char const *)this + Palettes);};
		unsigned char * Palette_Data(void) {return((unsigned char *)this + Palettes);};
		unsigned char const * Icon_Data(void) const {return((unsigned char const *)this + Icons);};
		unsigned char * Icon_Data(void) {return((unsigned char *)this + Icons);};
		unsigned char const * Map_Data(void) const {return((unsigned char const *)this + Map);};
		unsigned char * Map_Data(void) {return((unsigned char *)this + Map);};
		unsigned char const * Remap_Data(void) const {return((unsigned char const *)this + Remaps);};
		unsigned char * Remap_Data(void) {return((unsigned char *)this + Remaps);};
		unsigned char const * Trans_Data(void) const {return((unsigned char const *)this + TransFlag);};
		unsigned char * Trans_Data(void) {return((unsigned char *)this + TransFlag);};

	/*
	**	Disallow these operations with an IconsetClass object.
	*/
	private:
		IconsetClass & operator = (IconsetClass const &);
		IconsetClass(void);
		static void * operator new(size_t);
};


#endif
