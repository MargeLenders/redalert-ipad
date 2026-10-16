/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef CARGO_H
#define CARGO_H

class FootClass;

/****************************************************************************
**	This class handles the basic cargo logic.
*/
class CargoClass {
	public:

		/*---------------------------------------------------------------------
		**	Constructors, Destructors, and overloaded operators.
		*/
		CargoClass(void) : Quantity(0), CargoHold(0) {};
		CargoClass(NoInitClass const & ) {};
		~CargoClass(void) {CargoHold=0;};

		/*---------------------------------------------------------------------
		**	Member function prototypes.
		*/

		#ifdef CHEAT_KEYS
		void Debug_Dump(MonoClass *mono) const;
		#endif
		void AI(void) {};

		int How_Many(void) const {return Quantity;};
		bool Is_Something_Attached(void) const {return (CargoHold != 0);};
		FootClass * Attached_Object(void) const;
		FootClass * Detach_Object(void);
		void Attach(FootClass * object);

		/*
		**	File I/O.
		*/
		void Code_Pointers(void);
		void Decode_Pointers(void);

	private:

		/*
		**	This is the number of objects attached to this cargo hold. For transporter
		**	objects, they might contain more than one object.
		*/
		unsigned char Quantity;

		/*
		**	This is the target value of any attached object. A value of zero indicates
		**	that no object is attached.
		*/
		FootClass * CargoHold;
};

#endif

