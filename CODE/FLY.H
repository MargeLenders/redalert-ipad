/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef FLY_H
#define FLY_H

typedef enum ImpactType {
	IMPACT_NONE,		// No movement (of significance) occurred.
	IMPACT_NORMAL,		// Some (non eventful) movement occurred.
	IMPACT_EDGE			// The edge of the world was reached.
} ImpactType;


/****************************************************************************
**	Flying objects are handled by this class definition.
*/
class FlyClass {
	public:
		/*---------------------------------------------------------------------
		**	Constructors, Destructors, and overloaded operators.
		*/
		FlyClass(void) : SpeedAccum(0), SpeedAdd(MPH_IMMOBILE) {};
		FlyClass(NoInitClass const &) {};
		~FlyClass(void) {};

		/*---------------------------------------------------------------------
		**	Member function prototypes.
		*/
		void Fly_Speed(int speed, MPHType maximum);
		ImpactType Physics(COORDINATE &coord, DirType facing);
		MPHType Get_Speed(void) const {return(SpeedAdd);};

	private:
		/*
		**	Object movement consists of incrementing the accumulator until enough "distance"
		**	has accumulated so that moving the object becomes reasonable.
		*/
		unsigned SpeedAccum;			// Lepton accumulator.
		MPHType SpeedAdd;			// Lepton add (per frame).
};

#endif
