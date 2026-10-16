/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef GSCREEN_H
#define GSCREEN_H

#include	"function.h"
#include	"cell.h"

class GScreenClass
{
	public:

		GScreenClass(void);
		GScreenClass(NoInitClass const &) {};

		/*
		** Initialization
		*/
		virtual void One_Time(void);							// One-time initializations
		virtual void Init(TheaterType = THEATER_NONE);	// Inits everything
		virtual void Init_Clear(void);						// Clears all to known state
		virtual void Init_IO(void);							// Inits button list
		virtual void Init_Theater(TheaterType theater);	// Theater-specific inits

		/*
		**	Player I/O is routed through here. It is called every game tick.
		*/
		virtual void Input(KeyNumType & key, int & x, int & y);
		virtual void AI(KeyNumType &, int, int) {};
		virtual void Add_A_Button(GadgetClass & gadget);
		virtual void Remove_A_Button(GadgetClass & gadget);

		/*
		**	Called when map needs complete updating.
		*/
		virtual void Flag_To_Redraw(bool complete=false);

		/*
		**	Render maintenance routine (call every game tick). Probably no need
		**	to override this in derived classes.
		*/
		virtual void Render(void);

		/*
		**	Is called when actual drawing is required. This is the function to
		**	override in derived classes.
		*/
		virtual void Draw_It(bool =false) {};

		/*
		**	This moves the hidpage up to the seenpage.
		*/
		virtual void Blit_Display(void);

		/*
		**	Changes the mouse shape as indicated.
		*/
		virtual void Set_Default_Mouse(MouseType mouse, bool wsmall) = 0;
		virtual bool Override_Mouse_Shape(MouseType mouse, bool wsmall) = 0;
		virtual void Revert_Mouse_Shape(void) = 0;
		virtual void Mouse_Small(bool wsmall) = 0;

		/*
		**	Misc routines.
		*/
		virtual void * Shadow_Address(void) {return(ShadowPage);};

		/*
		**	This points to the buttons that are used for input. All of the derived classes will
		**	attached their specific buttons to this list.
		*/
		static GadgetClass * Buttons;

	private:

		/*
		**	If the entire map is required to redraw, then this flag is true. This flag
		**	is set by the Flag_To_Redraw function. Typically, this occurs when the screen
		**	has been trashed or is first created.
		*/
		unsigned IsToRedraw:1;

		/*
		**	If only a sub-system of the map must be redrawn, then this flag will be set.
		**	An example of something that would set this flag would be an animating icon
		**	in the sidebar. In such a case, complete redrawing of the entire display is not
		**	necessary, but the Draw_It function should still be called so that the appropriate
		**	class can perform it's rendering.
		*/
		unsigned IsToUpdate:1;

		/*
		**	Pointer to an exact copy of the visible graphic page. This copy is used to speed
		**	display rendering by using an only-update-changed-pixels algorithm.
		*/
		static GraphicBufferClass * ShadowPage;
};

#endif
