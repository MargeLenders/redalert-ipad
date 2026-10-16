/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef ABSTRACT_H
#define ABSTRACT_H

DirType Direction(CELL cell1, CELL cell2);
DirType Direction(COORDINATE coord1, COORDINATE coord2);
int Distance(COORDINATE coord1, COORDINATE coord2);
COORDINATE As_Coord(TARGET target);

class AbstractTypeClass;

/*
**	This class is the base class for all game objects that have an existence on the
**	battlefield.
*/
class AbstractClass
{
	public:

		/*
		**	This specifies the type of object and the unique ID number
		**	associated with it. The ID number happens to match the index into
		**	the object heap appropriate for this object type.
		*/
		RTTIType RTTI;
		int ID;

		/*
		**	The coordinate location of the unit. For vehicles, this is the center
		**	point. For buildings, it is the upper left corner.
		*/
		COORDINATE Coord;

		/*
		**	This is the height of the object above ground (expressed in leptons).
		*/
		int Height;

		/*
		**	The actual object ram-space is located in arrays in the data segment. This flag
		**	is used to indicate which objects are free to be reused and which are currently
		**	in use by the game.
		*/
		unsigned IsActive:1;

		/*-----------------------------------------------------------------------------------
		**	Constructor & destructors.
		*/
		AbstractClass(RTTIType rtti, int id) : RTTI(rtti), ID(id), Coord(0xFFFFFFFFL), Height(0) {};
		AbstractClass(NoInitClass const & x) {x();};
		virtual ~AbstractClass(void) {};

		/*
		**	Query functions.
		*/
		virtual char const * Name(void) const {return("");}
		virtual HousesType Owner(void) const {return HOUSE_NONE;};
		TARGET As_Target(void) const {return(Build_Target(RTTI, ID));};
		RTTIType What_Am_I(void) const {return(RTTI);};

		/*
		**	Scenario and debug support.
		*/
		#ifdef CHEAT_KEYS
		virtual void Debug_Dump(MonoClass * mono) const;
		#endif

		/*
		**	Coordinate query support functions.
		*/
		virtual COORDINATE Center_Coord(void) const {return Coord;};
		virtual COORDINATE Target_Coord(void) const {return Coord;};

		/*
		**	Coordinate inquiry functions. These are used for both display and
		**	combat purposes.
		*/
		DirType Direction(AbstractClass const * object) const {return ::Direction(Center_Coord(), object->Target_Coord());};
		DirType Direction(COORDINATE coord) const {return ::Direction(Center_Coord(), coord);};
		DirType Direction(TARGET target) const {return ::Direction(Center_Coord(), As_Coord(target));};
		DirType Direction(CELL cell) const {return ::Direction(Coord_Cell(Center_Coord()), cell);};
		int Distance(TARGET target) const;
		int Distance(COORDINATE coord) const {return ::Distance(Center_Coord(), coord);};
		int Distance(AbstractClass const * object) const {return ::Distance(Center_Coord(), object->Target_Coord());};

		/*
		**	Object entry and exit from the game system.
		*/
		virtual MoveType Can_Enter_Cell(CELL , FacingType = FACING_NONE) const {return MOVE_OK;};

		/*
		**	AI.
		*/
		virtual void AI(void) {};

};


#endif
