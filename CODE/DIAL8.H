/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef DIAL8_H
#define DIAL8_H

class Dial8Class : public ControlClass
{
	public:
		/*
		** Constructor/Destructor
		*/
		Dial8Class(int id, int x, int y, int w, int h, DirType dir);

		/*
		** Get/Set the direction the dial is currently pointing
		*/
		DirType Get_Direction(void) const;
		void Set_Direction(DirType dir);

		/*
		** Overloaded draw routine
		*/
		virtual int Draw_Me(int forced = false);

	protected:
		/*
		** Overloaded event processing routine
		*/
		virtual int Action(unsigned flags, KeyNumType &key);

	private:
		int FaceX;						// x-coord of center of face
		int FaceY;						// y-coord of center of face
		int FacePoint[8][2];			// coords of the little dial decorations
		int FaceLine[8][2];			// coords for drawing the dial hand
		DirType Direction;			// 0-255 numerical direction of dial
		FacingType Facing;			// numerical facing direction of dial (0 - 7)
		FacingType OldFacing;		// previous Facing value

};

#endif

