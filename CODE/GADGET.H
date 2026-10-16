/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef GADGET_H
#define GADGET_H

#include "link.h"

class ControlClass;

class GadgetClass : public LinkClass
{
	public:
		typedef enum FlagEnum {
			LEFTPRESS    = 0x0001,	// Left mouse button press.
			LEFTHELD     = 0x0002,	// Left mouse button is being held down.
			LEFTRELEASE  = 0x0004,	// Left mouse button released.
			LEFTUP       = 0x0008,	// Left mouse button is being held up.
			RIGHTPRESS   = 0x0010,	// Right mouse button press.
			RIGHTHELD    = 0x0020,	// Right mouse button is being held down.
			RIGHTRELEASE = 0x0040,	// Right mouse button released.
			RIGHTUP      = 0x0080,	// Right mouse button is being held up.
			KEYBOARD     = 0x0100	// Keyboard input processing (maybe).
		} FlagEnum;

		GadgetClass(int x, int y, int w, int h, unsigned flags, int sticky=false);
		GadgetClass(NoInitClass const & x) : LinkClass(x) {};
		GadgetClass(void) {};
		GadgetClass(GadgetClass const & gadget);
		virtual ~GadgetClass(void);

		/*
		**	Gadget list management functions.
		*/
		virtual KeyNumType Input(void);
		virtual void Draw_All(bool forced=true);
		virtual void Delete_List(void);
		virtual ControlClass * Extract_Gadget(unsigned id);
		virtual void Flag_List_To_Redraw(void) {LastList = 0;};
		virtual GadgetClass * Remove(void);
		virtual GadgetClass * Get_Next(void) const;
		virtual GadgetClass * Get_Prev(void) const;

		/*
		**	Manages individual gadget states and actions.
		*/
		virtual void Disable(void);
		virtual void Enable(void);
		virtual unsigned Get_ID(void) const {return 0;};
		virtual void Flag_To_Redraw(void);
		virtual void Peer_To_Peer(unsigned , KeyNumType & , ControlClass & ) {};
		virtual void Set_Focus(void);
		virtual void Clear_Focus(void);
		virtual bool Has_Focus(void);
		virtual int  Is_List_To_Redraw(void);
		virtual bool Is_To_Redraw(void) {return (IsToRepaint);}
		virtual void Set_Position(int x, int y);

		/*
		**	General render function.
		*/
		virtual int Draw_Me(int forced=false);

		/*
		** Sets the current color scheme
		*/
		static void Set_Color_Scheme(RemapControlType *scheme)
			{ ColorScheme = scheme; }

		static RemapControlType * Get_Color_Scheme(void)
			{ return (ColorScheme); }

		/*
		**	This is the coordinates and dimensions of the gadget region. These are in
		**	absolute screen pixel coordinates.
		*/
		int X;
		int Y;
		int Width;
		int Height;

	protected:

		/*
		**	Processes the event flags so that if this gadget needs to "stick" or
		**	"unstick", it will be properly flagged. Call this function if you are
		**	going to clear the button press flags before calling the base class
		**	Action() function. Otherwise, calling this function manually, is
		**	unnecessary since the base class Action() function already does so.
		*/
		virtual void Sticky_Process(unsigned flags);

		/*
		**	This is the action function that will be called whenever the flags and mouse
		**	input indicates. This is the main method by which this button performs a useful
		**	function.
		*/
		virtual int Action(unsigned flags, KeyNumType & key);

		/*
		**	This is a record of the last list passed to the Input() function. If a list
		**	different than the last recorded one is detected, then the draw function is
		**	called for every gadget in the list. This causes all buttons to be redrawn the
		**	fire time Input() is called without forced a manual call to Draw_All().
		*/
		static GadgetClass * LastList;

		/*
		**	This points to the gadget that has the keyboard focus. All keyboard only
		**	events are fed to this gadget to the exclusion of all others.
		*/
		static GadgetClass * Focused;

		/*
		**	This button should call the Draw_Me function because some graphic element needs
		**	to be redrawn. This flag is set by default if the Action function is called.
		*/
		unsigned IsToRepaint:1;

	public:		// HACK HACK HACK.. this is here because the sidebar buttons are static.
		/*
		**	A sticky button is one that is processed to the exclusion of all other buttons
		**	IF the mouse was pressed down while over this button and the mouse continues
		**	to remain pressed. This is the standard behavior for all normal Windows style
		**	buttons.
		*/
		unsigned IsSticky:1;

		//	ajw - Publicized StuckOn 7/30/98 (was protected)
		/*
		**	If there is a sticky button being processed, then this will point to it. A sticky
		**	button is one that will ONLY be processed while the mouse button is being
		**	held down.
		*/
		static GadgetClass * StuckOn;

	protected:

		/*
		**	If the button is disabled, then it won't be processed by the input function. It will
		**	have its Draw_Me function called as necessary. In order to not display the button
		**	at all, the appropriate draw function should perform no action -- just return. Or,
		**	just remove the button from the list.
		*/
		unsigned IsDisabled:1;

		/*
		**	These are the action flags that are used to determine when the action function
		**	should be called. Example: If this gadget only wants the action button called when
		**	the left mouse button is pressed over the its region, then the flag will be set
		**	to LEFTPRESS.
		*/
		unsigned Flags;

		/*
		** This is the current color scheme; it must be initialized by the app.
		*/
		static RemapControlType *ColorScheme;

	private:
		virtual int Clicked_On(KeyNumType & key, unsigned flags, int x, int y);
};

inline GadgetClass::FlagEnum operator |(GadgetClass::FlagEnum left, GadgetClass::FlagEnum right) { return (GadgetClass::FlagEnum)((int)left | (int)right); }
inline GadgetClass::FlagEnum operator &(GadgetClass::FlagEnum left, GadgetClass::FlagEnum right) { return (GadgetClass::FlagEnum)((int)left & (int)right); }
inline GadgetClass::FlagEnum operator ~(GadgetClass::FlagEnum value) { return (GadgetClass::FlagEnum)(~(int)value); }


#endif
