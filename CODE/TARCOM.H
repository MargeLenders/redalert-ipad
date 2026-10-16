/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef TARCOM_H
#define TARCOM_H

#include	"turret.h"
#include	"bullet.h"

/****************************************************************************
**	Units that can perform combat are handled by this class. It performs
**	such operations as determining threat value down to actually launching the
**	projectile.
*/
class TarComClass : public TurretClass
{
	public:
		/*---------------------------------------------------------------------
		**	Constructors, Destructors, and overloaded operators.
		*/
		TarComClass(void) {};
		TarComClass(UnitType classid, HousesType house) : TurretClass(classid, house) {};
		virtual ~TarComClass(void);

		/*---------------------------------------------------------------------
		**	Member function prototypes.
		*/
		#ifdef CHEAT_KEYS
		virtual void Debug_Dump(MonoClass *mono) const;
		#endif
		virtual void AI(void);
//		virtual bool Target_Something_Nearby(ThreatType rangmatters=THREAT_NORMAL);

		/*
		**	File I/O.
		*/
		virtual void Code_Pointers(void);
		virtual void Decode_Pointers(void);

};

#endif


