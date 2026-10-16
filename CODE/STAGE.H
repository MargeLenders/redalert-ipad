/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef STAGE_H
#define STAGE_H

class StageClass {

		/*
		**	This handles the animation stage of the object. This includes smoke, walking,
		**	flapping, and rocket flames.
		*/
		unsigned Stage;

		/*
		**	This is the countdown timer for stage animation. When this counts down
		**	to zero, then the stage increments by one and the time cycle starts
		**	over again.
		*/
		CDTimerClass<FrameTimerClass> Timer;

		/*
		**	This is the value to assign the StageTimer whenever it needs to be reset. Thus,
		**	this value is the control of how fast the stage value increments.
		*/
		int Rate;

	public:
		StageClass(void) : Stage(0), Timer(0), Rate(0) {};
		StageClass(NoInitClass const & x) : Timer(x) {};

		int Fetch_Stage(void) const {return(Stage);};
		int Fetch_Rate(void) const {return(Rate);};
		void Set_Stage(int stage) {Stage = stage;};
		void Set_Rate(int rate) {Timer = rate; Rate = rate;};
		void AI(void) {};
		bool About_To_Change(void) const {return(Timer == 0 && Rate != 0);}
		bool Graphic_Logic(void) {
			if (About_To_Change()) {
				Stage++;
				Timer = Rate;
				return(true);
			}
			return(false);
		};
};


#endif
