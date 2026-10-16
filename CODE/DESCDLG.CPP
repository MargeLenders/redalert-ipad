/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#include	"function.h"
#include	"descdlg.h"


/***********************************************************************************************
 * DescriptionClass::Process -- Handles all the options graphic interface.                     *
 *                                                                                             *
 *    This dialog uses an edit box to "fill-out" a description.                                *
 *                                                                                             *
 * INPUT:      char *string - return answer here.                                              *
 * OUTPUT:     none                                                                            *
 * WARNINGS:   none                                                                            *
 * HISTORY:    12/31/1994 MML : Created.                                                       *
 *=============================================================================================*/
void DescriptionClass::Process(char * string)
{
	/*
	**	Set up the window.  Window x-coords are in bytes not pixels.
	*/
	Set_Window(WINDOW_EDITOR, OPTION_X, OPTION_Y, OPTION_WIDTH, OPTION_HEIGHT);
	Set_Logic_Page(SeenBuff);

	/*
	**	Create Buttons.  Button coords are in pixels, but are window-relative.
	*/
	TextButtonClass optionsbtn(BUTTON_OPTIONS, TXT_OK, TPF_BUTTON, 0, BUTTON_Y);
	TextButtonClass cancelbtn(BUTTON_CANCEL, TXT_CANCEL, TPF_BUTTON, 0, BUTTON_Y);

	cancelbtn.X  = OPTION_X + ((OPTION_WIDTH - optionsbtn.Width)/3)*2;
	optionsbtn.X = OPTION_X + ((OPTION_WIDTH - optionsbtn.Width)/3);
	optionsbtn.Add_Tail(cancelbtn);

	EditClass edit(
		BUTTON_EDIT,
		string,
		31,
		TPF_6PT_GRAD,
		0,
		EDIT_Y,
		EDIT_W);

	edit.Set_Focus();
	edit.X = OPTION_X + (OPTION_WIDTH - edit.Width)/2,
	optionsbtn.Add_Tail(edit);

	/*
	**	This causes left mouse button clicking within the confines of the dialog to
	**	be ignored if it wasn't recognized by any other button or slider.
	*/
	GadgetClass dialog(OPTION_X, OPTION_Y, OPTION_WIDTH, OPTION_HEIGHT, GadgetClass::LEFTPRESS);
	optionsbtn.Add_Tail(dialog);

	/*
	**	This causes a right click anywhere or a left click outside the dialog region
	**	to be equivalent to clicking on the return to options dialog.
	*/
	ControlClass background(BUTTON_OPTIONS, 0, 0, 320, 200, GadgetClass::LEFTPRESS|GadgetClass::RIGHTPRESS);
	optionsbtn.Add_Tail(background);

	/*
	**	Main Processing Loop
	*/
	bool display = true;
	bool process = true;
	while (process) {

		/*
		**	Invoke game callback
		*/
		Call_Back();

		/*
		**	Refresh display if needed
		*/
		if (display) {

			Window_Hide_Mouse(WINDOW_EDITOR);

			/*
			**	Draw the background
			*/
			Window_Box (WINDOW_EDITOR, BOXSTYLE_BORDER); // has border, raised up
			Draw_Caption(TXT_MISSION_DESCRIPTION, OPTION_X, OPTION_Y, OPTION_WIDTH);

			/*
			**	Draw the titles
			*/
			optionsbtn.Draw_All();
			Window_Show_Mouse();
			display = false;
		}

		/*
		**	Get user input
		*/
		KeyNumType input = optionsbtn.Input();

		/*
		**	Process Input
		*/
		switch (input) {

			case KN_RETURN:
			case KeyNumType(BUTTON_OPTIONS|KN_BUTTON):
				strtrim(string);
				process = false;
				break;

			case KN_ESC:
			case KeyNumType(BUTTON_CANCEL|KN_BUTTON):
				string[0]= NULL;
				strtrim(string);
				process = false;
				break;

			case KeyNumType(BUTTON_EDIT|KN_BUTTON):
				break;

			default:
				break;
		}
	}
}

