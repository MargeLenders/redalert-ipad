/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef FUSE_H
#define FUSE_H

/****************************************************************************
**	The fuse is used by projectiles to determine whether detonation should
**	occur. This is usually determined by tracking the distance to the
**	designated target reaches zero or when the timer expires.
*/
class FuseClass {
	public:
		FuseClass(void);
		FuseClass(NoInitClass const &) {};
		~FuseClass(void) {};

		void Arm_Fuse(COORDINATE location, COORDINATE target, int time=0xFF, int arming=0);
		bool Fuse_Checkup(COORDINATE newlocation);
		void Fuse_Write(FileClass & file);
		void Fuse_Read(FileClass & file);
		COORDINATE Fuse_Target(void);

		/*
		**	Fuses can detonate if enough time has elapsed. This value counts
		**	down. When it reaches zero, detonation occurs.
		*/
		unsigned char Timer;

	private:

		/*
		**	Some fuses need a certain amount of time before detonation can
		**	occur. This counts down and when it reaches zero, normal fuse
		**	detonation checking can occur.
		*/
		unsigned char Arming;

		/*
		**	This is the designated impact point of the projectile. The fuse
		**	will trip when the closest point to this location has been reached.
		*/
		COORDINATE HeadTo;

		/*
		**	This is the running proximity value to the impact point. This value
		**	will progressively get smaller. Detonation occurs when it reaches
		**	zero or when it starts to grow larger.
		*/
		short Proximity;
};

inline COORDINATE FuseClass::Fuse_Target(void)
{
	return(HeadTo);
}

#endif
