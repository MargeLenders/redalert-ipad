/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef FACING_H
#define FACING_H

/*
**	This is a general facing handler class. It is used in those cases where facing needs to be
**	kept track of, but there could also be an associated desired facing. The current facing
**	is supposed to transition to the desired state over time. Using this class facilitates this
**	processing as well as isolating the rest of the code from the internals.
*/
class FacingClass
{
	public:
		FacingClass(void);
		FacingClass(DirType dir) : CurrentFacing((DirType)(unsigned char)dir), DesiredFacing((DirType)(unsigned char)dir) {};
		FacingClass(NoInitClass const & ) {};

		operator DirType (void) const {return(CurrentFacing);};

		DirType Current(void) const {return(CurrentFacing);};
		DirType Desired(void) const {return(DesiredFacing);};

		int Set_Desired(DirType facing);
		int Set_Current(DirType facing);

		void Set(DirType facing) {
			Set_Current(facing);
			Set_Desired(facing);
		};

		DirType Get(void) const { return CurrentFacing; }

		int Is_Rotating(void) const {return (DesiredFacing != CurrentFacing);};
		int Difference(void) const {return (int)(signed char)((int)DesiredFacing - (int)CurrentFacing);}
		int Difference(DirType facing) const {return (int)(signed char)((int)facing - (int)CurrentFacing);}
		int Rotation_Adjust(int rate);

	private:
		DirType CurrentFacing;
		DirType DesiredFacing;
};


#endif
