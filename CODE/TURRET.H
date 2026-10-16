/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef TURRET_H
#define TURRET_H

#include "drive.h"

class TurretClass : public DriveClass
{
	public:

		/*
		**	File I/O.
		*/
		virtual void Code_Pointers(void);
		virtual void Decode_Pointers(void);

	protected:
		TurretClass(UnitType classid, HousesType house);
		TurretClass(void);
		virtual ~TurretClass(void);
};


#endif
