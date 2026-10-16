/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef CREW_H
#define CREW_H


/****************************************************************************
**	This class handles the basic crew logic. This includes hero tracking,
**	crew bail-out, and attached object logic.
*/
class CrewClass
{
	public:
		/*
		**	This keeps track of the number of "kills" the unit as accumulated.
		**	When it reaches a certain point, the unit improves.
		*/
		unsigned short Kills;

		/*
		**	Constructors, Destructors, and overloaded operators.
		*/
		CrewClass(void) : Kills(0) {};
		CrewClass(NoInitClass const &) {};
		~CrewClass(void) {};

		int Made_A_Kill(void) {
			Kills++;
			return(Kills);
		};

	private:
};

#endif
