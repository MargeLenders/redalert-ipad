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


/***********************************************************************************************
 * ControlClass::ControlClass -- Constructor for control class objects.                        *
 *                                                                                             *
 *    This is the normal constructor for control class objects. At this level, it only needs   *
 *    to record the ID number assigned to this button.                                         *
 *                                                                                             *
 * INPUT:   id    -- The ID number for this gadget. If the ID number specified is 0, then      *
 *                   this tells the system that no special ID code should be returned.         *
 *                                                                                             *
 *          x,y   -- Pixel coordinate of upper left corner of gadget's region.                 *
 *                                                                                             *
 *          w,h   -- Pixel dimensions of the gadget's region.                                  *
 *                                                                                             *
 *          flags -- The input event flags that this gadget recognizes.                        *
 *                                                                                             *
 *          sticky-- This this a "sticky" gadget? A sticky gadget is one that takes over the   *
 *                   gadget list while the mouse button is held down, if the mouse button was  *
 *                   initially clicked over its region. This is the behavior of "normal"       *
 *                   buttons in Windows.                                                       *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/15/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
ControlClass::ControlClass(unsigned id, int x, int y, int w, int h, unsigned flags, int sticky) :
	GadgetClass(x, y, w, h, flags, sticky),
	ID(id),
	Peer(0)
{
}


/***********************************************************************************************
 * ControlClass::ControlClass -- Copy constructor for control gadget.                          *
 *                                                                                             *
 *    This copy constructor for a control gadget is used create a duplicate gadget that        *
 *    is functionally similar.                                                                 *
 *                                                                                             *
 * INPUT:   control  -- Reference to the gadget that is to be copied.                          *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/05/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
ControlClass::ControlClass(ControlClass const & control) :
	GadgetClass(control),
	ID(control.ID),
	Peer(control.Peer)
{
}

/***********************************************************************************************
 * ControlClass::Action -- Normal action for control gadget objects.                           *
 *                                                                                             *
 *    This function gets called when the input event that this control gadget is looking for   *
 *    occurs. In such a case, the return key code value is changed to the gadget's ID number   *
 *    with the special button bit flag attached.                                               *
 *                                                                                             *
 * INPUT:   flags -- The event that triggered this function call. If this value is NULL, then  *
 *                   this is a forced (probably due to the sticky flag) call and the key code  *
 *                   is not altered.                                                           *
 *                                                                                             *
 *          key   -- Reference to the key code that will be returned by the controlling        *
 *                   Input() function.                                                         *
 *                                                                                             *
 * OUTPUT:  bool; Should further list processing be aborted?                                   *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/15/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
int ControlClass::Action(unsigned flags, KeyNumType & key)
{

	/*
	**	Only if the flags indicate that a recognized action has occurred, do the
	**	normal processing of this gadget and set return value to the gadget ID.
	*/
	if (flags) {
		if (ID) {
			key = (KeyNumType)(ID | KN_BUTTON);
		} else {
			key = KN_NONE;
		}
	}

	/*
	**	If there is a peer link established, inform that gadget of this
	**	action call.
	*/
	if (Peer) {
		Peer->Peer_To_Peer(flags, key, *this);
	}

	return(GadgetClass::Action(flags, key));
}


/***********************************************************************************************
 * ControlClass::Make_Peer -- Assigns a peer gadget to this gadget.                            *
 *                                                                                             *
 *    This function will assign another gadget to this one. That other gadget will receive     *
 *    notification of any Action() call to this gadget. Presumably, this is how one gadget     *
 *    can automatically adapt to changes in another. Say for example, a slider bar can affect  *
 *    the list box it is attached to.                                                          *
 *                                                                                             *
 * INPUT:   gadget   -- The gadget to inform when any Action() function is called.             *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/16/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
void ControlClass::Make_Peer(GadgetClass & gadget)
{
	Peer = &gadget;
}


/***********************************************************************************************
 * ControlClass::Get_ID -- Gets the ID number for this gadget.                                 *
 *                                                                                             *
 *    This function will query and return with the ID number for this gadget. It is primarily  *
 *    used by the Extract_Gadget() function.                                                   *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  Returns with the ID number for this gadget. If zero is returned, this means that   *
 *          no ID was assigned to this gadget. This is a special case since a zero value will  *
 *          never be returned as a pseudo-key as is done with non-zero values.                 *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/16/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
unsigned ControlClass::Get_ID(void) const
{
	return(ID);
}


/***********************************************************************************************
 * ControlClass::Draw_Me -- Draw logic for the control class object.                           *
 *                                                                                             *
 *    This is called when the control object might need to be redrawn or when redrawing is     *
 *    necessary. Since at this level of the class hierarchy, no actual drawing occurs, this    *
 *    routine doesn't perform any rendering. It does, however, inform any peer attached        *
 *    object that a Draw_Me function has been called. Presumably, the attached peer gadget     *
 *    might very well need to be redrawn as a result of some action by this gadget. Since this *
 *    gadget might, more than likely, be of the "sticky" variety, a normal call to Draw_Me     *
 *    for the other gadget will not occur. It must rely on the call by this routine in order   *
 *    to update correctly. A typical example of this would be a slider that is attached to     *
 *    a list box. As the slider is being drug around, the attached list box must be redrawn.   *
 *                                                                                             *
 * INPUT:   forced   -- Should the redraw be forced regardless of the redraw flag?             *
 *                                                                                             *
 * OUTPUT:  bool; Was the gadget redrawn?                                                      *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/16/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
int ControlClass::Draw_Me(int forced)
{
	if (Peer) {
		Peer->Draw_Me();
	}
	return(GadgetClass::Draw_Me(forced));
}
