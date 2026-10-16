/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef SPECIAL_H
#define SPECIAL_H

class SpecialClass
{
	public:

		/*
		**	This initializes all members just like a constructor. A constructor
		**	cannot be used for this class because it is part of a union.
		*/
		void Init(void);

		/*
		**	If the shroud should regenerated, then this flag will be true.
		*/
		unsigned IsShadowGrow:1;

		/*
		**	Controls the speedy build option -- used for testing.
		*/
		unsigned IsSpeedBuild:1;

		/*
		** If from install, then play the special installation movie and
		** skip asking them what type of game they want to play.
		*/
		unsigned IsFromInstall:1;

		/*
		**	If capture the flag mode is on, this flag will be true. With this
		**	flag enabled, then the flag is initially placed at the start of
		**	the scenario.
		*/
		unsigned IsCaptureTheFlag:1;

		/*
		**	This flags controls whether weapons are inert. An inert weapon doesn't do any
		**	damage. Effectively, if this is true, then the units never die.
		*/
		unsigned IsInert:1;

		/*
		**	If wheeled vehicles should do a 3-point turn when rotating in place, then
		**	this flag is true.
		*/
		unsigned IsThreePoint:1;

		/*
		**	If Tiberium is allowed to spread and grow, then these flags will be true.
		**	These are duplicated from the rules.ini file and also controlled by the
		**	multiplayer dialog box.
		*/
		unsigned IsTGrowth:1;
		unsigned IsTSpread:1;

		/*
		** Flag that we were spawned from WChat.
		*/
		unsigned IsFromWChat:1;
};


#endif
