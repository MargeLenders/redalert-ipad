/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef GAUGE_H
#define GAUGE_H

class GaugeClass : public ControlClass
{
	public:

		GaugeClass(unsigned id, int x, int y, int w, int h);

		virtual int Draw_Me(int forced=false);
		virtual int Set_Maximum(int value);
		virtual int Set_Value(int value);
		virtual int Get_Value(void) const {return (CurValue);};
		virtual void Use_Thumb(int value) { HasThumb = value ? true : false; };

		virtual int Thumb_Pixels(void) { return (4);}

		/*
		**	If this gauge has a color to the left of the current setting, then this
		**	flag will be true.
		*/
		unsigned IsColorized:1;

	protected:

		/*
		**	If a thumb is desired, set to true.
		*/
		unsigned HasThumb:1;

		/*
		**	Is this a horizontal slider?
		*/
		unsigned IsHorizontal:1;

		int MaxValue;				// maximum value (in application units)
		int CurValue;				// index of 1st displayed string in box
										//  (in application units)

		/*
		** This value records the difference between where the user clicked
		** and the edge of the thumb, so that the thumb follows the mouse
		** with the proper offset.
		*/
		int ClickDiff;

	protected:
		virtual void Draw_Thumb(void);
		virtual int  Action(unsigned flags, KeyNumType &key);
		virtual int  Pixel_To_Value(int pixel);
		virtual int  Value_To_Pixel(int value);
};



class TriColorGaugeClass : public GaugeClass
{
	public:
		TriColorGaugeClass(unsigned id, int x, int y, int w, int h);
		virtual int Draw_Me(int forced);
		virtual int Set_Red_Limit(int value);
		virtual int Set_Yellow_Limit(int value);

	protected:
		int RedLimit;				// maximum value for red
		int YellowLimit;			// maximum value for yellow
};




#endif
