/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef POWER_H
#define POWER_H

#include	"radar.h"

class PowerClass : public RadarClass
{
	public:
		PowerClass(void);
		PowerClass(NoInitClass const & x) : RadarClass(x), FlashTimer(x) {};

		/*
		** Initialization
		*/
		virtual void One_Time(void);							// One-time inits

		virtual void Init_Clear(void);						// Clears all to known state
		virtual void Draw_It(bool complete=false);
		virtual void AI(KeyNumType &input, int x, int y);
		virtual void Refresh_Cells(CELL cell, short const *list);
		void Flash_Power(void);

		unsigned IsToRedraw:1;

	protected:
		/*
		**	This gadget is used to capture mouse input on the power bar.
		*/
		class PowerButtonClass : public GadgetClass {
			public:
				PowerButtonClass(void) : GadgetClass(0,0,0,0,LEFTPRESS|LEFTRELEASE|LEFTHELD|LEFTUP|RIGHTPRESS,true) {};

			protected:
				virtual int Action(unsigned flags, KeyNumType & key);
			friend class PowerClass;
		};

		/*
		**	This is the "button" that tracks all input to the tactical map.
		** It must be available to derived classes, for Save/Load purposes.
		*/
		static PowerButtonClass PowerButton;

		enum PowerEnums {
			POWER_X=10*ICON_PIXEL_W,
#ifdef WIN32
			POWER_Y= (7+70+13),
			POWER_HEIGHT=(200-(7+70+13)),
#else
			POWER_Y= (88+9),
			POWER_HEIGHT=80,
#endif
			POWER_WIDTH=8,
			POWER_LINE_SPACE=5,
			POWER_LINE_WIDTH=3,
			POWER_STEP_LEVEL=100,
			POWER_STEP_FACTOR=5
		};

	private:
		int Power_Height(int value);

		unsigned IsActive:1;

		/*
		**	If the power bar should be rendered with some flash effect then
		**	this specifies the duration that the flash will occur.
		*/
		CDTimerClass<FrameTimerClass> FlashTimer;

		int RecordedDrain;
		int RecordedPower;
		int DesiredDrainHeight;
		int DesiredPowerHeight;
		int DrainHeight;
		int PowerHeight;
		int DrainBounce;
		int PowerBounce;
		short PowerDir;
		short DrainDir;

		/*
		**	Points to the shape to use for the "desired" power level indicator.
		*/
		static void const * PowerShape;
		static void const * PowerBarShape;
};

#endif
