/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef DOOR_H
#define DOOR_H

class DoorClass
{
	private:

		/*
		**	This is the animation control handler.
		*/
		StageClass Control;

		/*
		**	This is the recorded number of stages of the current
		**	door animation process.
		*/
		unsigned char Stages;

		/*
		**	This is the door state.
		*/
		enum {
			IS_CLOSED,		// Door is closed.
			IS_OPENING,		// Door is in the process of opening.
			IS_OPEN,			// Door is fully open.
			IS_CLOSING		//	Door is in the process of closing.
		} State;

		/*
		**	If the animation for this door indicates that the object it is
		**	attached to should be redrawn, then this flag will be true.
		*/
		unsigned IsToRedraw:1;

	public:
		DoorClass(void);
		DoorClass(NoInitClass const & x) : Control(x) {};

		bool Time_To_Redraw(void) {return(IsToRedraw);};
		void Clear_Redraw_Flag(void) {IsToRedraw = false;};
		void AI(void);
		int Door_Stage(void) const;
		bool Is_Door_Opening(void) const {return(State == IS_OPENING);};
		bool Is_Door_Closing(void) const {return(State == IS_CLOSING);};
		bool Open_Door(int rate, int stages);
		bool Close_Door(int rate, int stages);
		bool Is_Door_Open(void) const {return(State == IS_OPEN);};
		bool Is_Door_Closed(void) const {return(State == IS_CLOSED);};
		bool Is_Ready_To_Open(void) const;
};

#endif
