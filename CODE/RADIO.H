/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef RADIO_H
#define RADIO_H

#include	"mission.h"

class ObjectClass;
class TechnoClass;


/****************************************************************************
**	Radio contact is controlled by this class. It handles the mundane chore
**	of keeping the radio contact alive as well as broadcasting messages
**	to the receiving radio. Radio contact is primarily used when one object
**	is in "command" of another.
*/
class RadioClass : public MissionClass {
	private:

		/*
		**	This is a record of the last message received by this receiver.
		*/
		RadioMessageType Old[3];

		/*
		**	This is the object that radio communication has been established
		**	with. Although is is only a one-way reference, it is required that
		**	the receiving radio is also tuned to the object that contains this
		**	radio set.
		*/
		RadioClass * Radio;

		/*
		**	This is a text representation of all the possible radio messages. This
		**	text is used for monochrome debug printing.
		*/
		static char const * Messages[RADIO_COUNT];

	public:

		/*---------------------------------------------------------------------
		**	Constructors, Destructors, and overloaded operators.
		*/
		RadioClass(RTTIType rtti, int id) : MissionClass(rtti, id), Radio(0) {};
		RadioClass(NoInitClass const & x) : MissionClass(x) {};
		virtual ~RadioClass(void) {Radio=0;};

		/*---------------------------------------------------------------------
		**	Member function prototypes.
		*/
		bool In_Radio_Contact(void) const {return (Radio != 0);};
		void Radio_Off(void) {Radio = 0;};
		TechnoClass * Contact_With_Whom(void) const {return (TechnoClass *)Radio;};

		// Inherited from base class(es).
		virtual RadioMessageType Receive_Message(RadioClass * from, RadioMessageType message, long & param);
		virtual RadioMessageType Transmit_Message(RadioMessageType message, long & param=LParam, RadioClass * to=NULL);
		virtual RadioMessageType Transmit_Message(RadioMessageType message, RadioClass * to);
		#ifdef CHEAT_KEYS
		virtual void Debug_Dump(MonoClass *mono) const;
		#endif
		virtual bool Limbo(void);

		/*
		**	File I/O.
		*/
		virtual void Code_Pointers(void);
		virtual void Decode_Pointers(void);
};

#endif
