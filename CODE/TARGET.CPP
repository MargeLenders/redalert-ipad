/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#include	"function.h"
#include	"target.h"


TargetClass::TargetClass(TARGET target)
{
	Target.Target = target;
}


TargetClass::TargetClass(AbstractClass const * ptr) {
	if (ptr != NULL) {
		Target.Sub.Exponent = ptr->RTTI;
		Target.Sub.Mantissa = ptr->ID;
	} else {
		Target.Sub.Exponent = RTTI_NONE;
	}
}

TargetClass::TargetClass(AbstractTypeClass const * ptr) {
	if (ptr != NULL) {
		Target.Sub.Exponent = ptr->RTTI;
		Target.Sub.Mantissa = ptr->ID;
	} else {
		Target.Sub.Exponent = RTTI_NONE;
	}
}

TargetClass::TargetClass(CellClass const * ptr) {
	if (ptr != NULL) {
		Target.Sub.Exponent = RTTI_CELL;
		Target.Sub.Mantissa = ptr->ID;
	} else {
		Target.Sub.Exponent = RTTI_NONE;
	}
}

CellClass * xTargetClass::As_Cell(void) const
{
	if (Target.Sub.Exponent == RTTI_CELL) {
		return(&Map[(CELL)Target.Sub.Mantissa]);
	}
	return(NULL);
}


/***********************************************************************************************
 * As_Trigger -- Converts specified target into a trigger pointer.                             *
 *                                                                                             *
 *    This routine will convert the specified target number into a trigger pointer.            *
 *                                                                                             *
 * INPUT:   target   -- The target number to convert.                                          *
 *                                                                                             *
 * OUTPUT:  Returns with the trigger pointer that the specified target number represents. If   *
 *          it doesn't represent a legal trigger object, then NULL is returned.                *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/08/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
TriggerClass * As_Trigger(TARGET target)
{
	return(Is_Target_Trigger(target) ? Triggers.Raw_Ptr(Target_Value(target)) : NULL);
}


/***********************************************************************************************
 * As_Team -- Converts a target number into a team pointer.                                    *
 *                                                                                             *
 *    This routine will convert the specified target number into a team pointer.               *
 *                                                                                             *
 * INPUT:   target   -- The target number to convert.                                          *
 *                                                                                             *
 * OUTPUT:  Returns with the team object that the specified target number represents. If it    *
 *          doesn't represent a legal team then NULL is returned.                              *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/08/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
TeamClass * As_Team(TARGET target)
{
	return(Is_Target_Team(target) ? Teams.Raw_Ptr(Target_Value(target)) : NULL);
}


/***********************************************************************************************
 * As_TeamType -- Converts a target into a team type pointer.                                  *
 *                                                                                             *
 *    This routine will convert the specified target number into a team type pointer.          *
 *                                                                                             *
 * INPUT:   target   -- The target number to convert.                                          *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the team type represented by the target number. If the   *
 *          target number doesn't represent a legal team type, then NULL is returned.          *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/08/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
TeamTypeClass * As_TeamType(TARGET target)
{
	return(Is_Target_TeamType(target) ? TeamTypes.Raw_Ptr(Target_Value(target)) : NULL);
}


/***********************************************************************************************
 * As_Animation -- Converts target value into animation pointer.                               *
 *                                                                                             *
 *    This routine will convert the specified target number into an animation pointer.         *
 *                                                                                             *
 * INPUT:   target   -- The target number to convert into an animation pointer.                *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the legal animation that this target represents. If it   *
 *          doesn't represent a legal animation, then NULL is returned.                        *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/08/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
AnimClass * As_Animation(TARGET target)
{
	return(Is_Target_Animation(target) ? Anims.Raw_Ptr(Target_Value(target)) : NULL);
}


/***********************************************************************************************
 * As_Bullet -- Converts the target into a bullet pointer.                                     *
 *                                                                                             *
 *    This routine will convert the specified target number into a bullet pointer.             *
 *                                                                                             *
 * INPUT:   target   -- The target number to convert.                                          *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the bullet it specifies. If the target doesn't refer to  *
 *          a legal bullet, then NULL is returned.                                             *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/08/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
BulletClass * As_Bullet(TARGET target)
{
	return(Is_Target_Bullet(target) ? Bullets.Raw_Ptr(Target_Value(target)) : NULL);
}


/***********************************************************************************************
 * As_Aircraft -- Converts the target value into an aircraft pointer.                          *
 *                                                                                             *
 *    This routine will convert the specified target value into an aircraft object pointer.    *
 *                                                                                             *
 * INPUT:   target   -- The target value to convert.                                           *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the aircraft that this target value represents. If the   *
 *          specified target value doesn't represent an aircraft, then NULL is returned.       *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/27/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
AircraftClass * As_Aircraft(TARGET target)
{
	return(Is_Target_Aircraft(target) ? Aircraft.Raw_Ptr(Target_Value(target)) : NULL);
}


/***********************************************************************************************
 * As_Techno -- Converts a target value into a TechnoClass pointer.                            *
 *                                                                                             *
 *    This routine will take the target value specified and convert it into a TechnoClass      *
 *    pointer if the target represents an object that has a TechnoClass.                       *
 *                                                                                             *
 * INPUT:   target   -- The target value to convert into a TechnoClass pointer.                *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the associated object's TechnoClass. If the target       *
 *          cannot be converted into a TechnoClass pointer, then NULL is returned.             *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   06/02/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
TechnoClass * As_Techno(TARGET target)
{
	ObjectClass * obj = As_Object(target);

	if (obj && obj->Is_Techno()) {
		return(TechnoClass *)obj;
	}
	return(NULL);
}


/***********************************************************************************************
 * As_Object -- Converts a target value into an object pointer.                                *
 *                                                                                             *
 *    This routine is used to convert the target value specified into an object pointer. If    *
 *    the target doesn't represent an object or the target value is illegal, then NULL is      *
 *    returned.                                                                                *
 *                                                                                             *
 * INPUT:   target   -- The target value to convert from.                                      *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the object it represent, or NULL if not an object.       *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/27/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
ObjectClass * As_Object(TARGET target)
{
	int val = Target_Value(target);
	ObjectClass * object = NULL;
	switch (Target_Kind(target)) {
		case RTTI_INFANTRY:
			object = Infantry.Raw_Ptr(val);
			break;

		case RTTI_UNIT:
			object = Units.Raw_Ptr(val);
			break;

		case RTTI_VESSEL:
			object = Vessels.Raw_Ptr(val);
			break;

		case RTTI_BUILDING:
			object = Buildings.Raw_Ptr(val);
			break;

		case RTTI_AIRCRAFT:
			object = Aircraft.Raw_Ptr(val);
			break;

		case RTTI_TERRAIN:
			object = Terrains.Raw_Ptr(val);
			break;

		case RTTI_BULLET:
			object = Bullets.Raw_Ptr(val);
			break;

		case RTTI_ANIM:
			object = Anims.Raw_Ptr(val);
			break;

		default:
			break;
	}

	/*
	**	Special check to ensure that a target value that references an
	**	invalid object will not be converted back into an object pointer.
	**	This condition is rare, but could occur in a network game if the
	**	object it refers to is destroyed between the time an event message
	**	is sent and when it is received.
	*/
	if (object != NULL && !object->IsActive) {
		object = NULL;
	}

	return(object);
}


/***********************************************************************************************
 * As_Unit -- Converts a target value into a unit pointer.                                     *
 *                                                                                             *
 *    This routine is used to convert the target value specified into a pointer to a unit      *
 *    object.                                                                                  *
 *                                                                                             *
 * INPUT:   target   -- The target value to convert into a unit pointer.                       *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the unit the target value represents or NULL if not      *
 *          a unit.                                                                            *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/27/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
UnitClass * As_Unit(TARGET target)
{
	return(Is_Target_Unit(target) ? Units.Raw_Ptr(Target_Value(target)) : NULL);
}


/***********************************************************************************************
 * As_Vessel -- Converts a target number into a vessel pointer.                                *
 *                                                                                             *
 *    Use this routine to conver the specified target number into a pointer to a vessel object *
 *    that it represents.                                                                      *
 *                                                                                             *
 * INPUT:   target   -- The target number to convert to a vessel pointer.                      *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the vessel object that this target value represents. If  *
 *          the target number does not represent a vessel, then null is returned.              *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/16/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
VesselClass * As_Vessel(TARGET target)
{
	return(Is_Target_Vessel(target) ? Vessels.Raw_Ptr(Target_Value(target)) : NULL);
}


/***********************************************************************************************
 * As_Infantry -- If the target is infantry, return a pointer to it.                           *
 *                                                                                             *
 *    This routine will translate the specified target value into an infantry pointer if the   *
 *    target actually represents an infantry object.                                           *
 *                                                                                             *
 * INPUT:   target   -- The target to convert to a pointer.                                    *
 *                                                                                             *
 * OUTPUT:  Returns a pointer to the infantry object that this target value represents. If     *
 *          the target doesn't represent an infantry object, then return NULL.                 *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   10/17/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
InfantryClass * As_Infantry(TARGET target)
{
	return(Is_Target_Infantry(target) ? Infantry.Raw_Ptr(Target_Value(target)) : NULL);
}


/***********************************************************************************************
 * As_Building -- Converts a target value into a building object pointer.                      *
 *                                                                                             *
 *    This routine is used to convert the target value specified into a building pointer.      *
 *                                                                                             *
 * INPUT:   target   -- The target value to convert from.                                      *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the building object that the target value represents.    *
 *          If it doesn't represent a building, then return NULL.                              *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/27/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
BuildingClass * As_Building(TARGET target)
{
	return(Is_Target_Building(target) ? Buildings.Raw_Ptr(Target_Value(target)) : NULL);
}


#ifdef NEVER
/***********************************************************************************************
 * Target_Legal -- Determines if the specified target is legal.                                *
 *                                                                                             *
 *    This routine is used to check for the legality of the target value specified. It is      *
 *    necessary to call this routine if there is doubt about the the legality of the target.   *
 *    It is possible for the unit that a target value represents to be eliminated and thus     *
 *    rendering the target value invalid.                                                      *
 *                                                                                             *
 * INPUT:   target   -- The target value to check.                                             *
 *                                                                                             *
 * OUTPUT:  bool; Is the target value legal?                                                   *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/27/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
bool Target_Legal(TARGET target)
{
	if (!Target_Legal(target)) return(false);

	ObjectClass * obj = As_Object(target);
	if (obj) {
		return(obj->Get_Strength() > 0 && obj->IsActive && !obj->IsInLimbo && obj->Class_Of().IsLegalTarget);
	}
	return(true);
}
#endif


/***********************************************************************************************
 * As_Cell -- Converts a target value into a cell number.                                      *
 *                                                                                             *
 *    This routine is used to convert the target value specified, into a cell value. This is   *
 *    necessary for find path and other procedures that need a cell value.                     *
 *                                                                                             *
 * INPUT:   target   -- The target value to convert to a cell value.                           *
 *                                                                                             *
 * OUTPUT:  Returns with the target value expressed as a cell location.                        *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/27/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
CELL As_Cell(TARGET target)
{
	return(Coord_Cell(As_Coord(target)));
}


/***********************************************************************************************
 * As_Coord -- Converts a target value into a coordinate value.                                *
 *                                                                                             *
 *    This routine is used to convert the target value specified into a coordinate value. It   *
 *    is necessary for those procedures that require a coordinate value.                       *
 *                                                                                             *
 * INPUT:   target   -- The target value to convert.                                           *
 *                                                                                             *
 * OUTPUT:  Returns with the target expressed as a COORDINATE value.                           *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/27/1994 JLB : Created.                                                                 *
 *   11/16/1994 JLB : Simplified.                                                              *
 *=============================================================================================*/
COORDINATE As_Coord(TARGET target)
{
	if (Target_Legal(target)) {
		/*
		**	Cell target values are handled as a special case. The value of the target number is
		**	actually the cell index number.
		*/
		if (Is_Target_Cell(target)) {
			int v = Target_Value(target);

			int x = ((v & 0x0FFF) << 4) + 0x0008;
			int y = (((v>>12) & 0x0FFF) << 4) + 0x0008;
			return(XY_Coord(x, y));

//			return(Cell_Coord((CELL)Target_Value(target)));
		}

		/*
		**	Normal targets correspond to game objects. Fetch the object pointer and then ask it
		**	for the center coordinate. Return the center coordinate as the target's coordinate.
		*/
		ObjectClass * obj = As_Object(target);
		if (obj != NULL) {
			assert(obj->IsActive);
			return(obj->Target_Coord());
		}
	}

	/*
	**	An unrecognized target value results in a null coordinate value.
	*/
	return(0x00000000L);
}


/***********************************************************************************************
 * As_Movement_Coord -- Fetches coordinate if trying to move to this target.                   *
 *                                                                                             *
 *    This routine will convert the specified target into a coordinate location. This location *
 *    is used when moving to the target specified. For cells, this is the center of the cell.  *
 *    For special buildings that allow docking, it is the center location of the docking       *
 *    bay.                                                                                     *
 *                                                                                             *
 * INPUT:   target   -- The target to convert into a coordinate value.                         *
 *                                                                                             *
 * OUTPUT:  Returns with the docking coordinate of the target value specified.                 *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/27/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
COORDINATE As_Movement_Coord(TARGET target)
{
	if (Target_Legal(target)) {
		/*
		**	Cell target values are handled as a special case. The value of the target number is
		**	actually the cell index number.
		*/
		if (Is_Target_Cell(target)) {
			return(Cell_Coord((CELL)Target_Value(target)));
		}

		/*
		**	Normal targets correspond to game objects. Fetch the object pointer and then ask it
		**	for the center coordinate. Return the center coordinate as the target's coordinate.
		*/
		ObjectClass * obj = As_Object(target);
		if (obj) {
			return(obj->Docking_Coord());
		}
	}

	/*
	**	An unrecognized target value results in a null coordinate value.
	*/
	return(0x00000000L);
}


/***********************************************************************************************
 * TargetClass::As_Object -- Converts a target into an object pointer.                         *
 *                                                                                             *
 *    If the target represents an object of some type, then this routine will return a         *
 *    pointer to the object. Otherwise it will return NULL.                                    *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the object that this target represents or NULL if it     *
 *          doesn't represent a target.                                                        *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   03/05/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
AbstractClass * xTargetClass::As_Abstract(void) const
{
	switch ((RTTIType)*this) {
		case RTTI_TEAM:
			return(Teams.Raw_Ptr(Value()));

		case RTTI_BULLET:
			return(Bullets.Raw_Ptr(Value()));

		case RTTI_OVERLAY:
			return(Overlays.Raw_Ptr(Value()));

		case RTTI_SMUDGE:
			return(Smudges.Raw_Ptr(Value()));

		case RTTI_UNIT:
			return(Units.Raw_Ptr(Value()));

		case RTTI_VESSEL:
			return(Vessels.Raw_Ptr(Value()));

		case RTTI_BUILDING:
			return(Buildings.Raw_Ptr(Value()));

		case RTTI_INFANTRY:
			return(Infantry.Raw_Ptr(Value()));

		case RTTI_AIRCRAFT:
			return(Aircraft.Raw_Ptr(Value()));

		case RTTI_TERRAIN:
			return(Terrains.Raw_Ptr(Value()));

		case RTTI_ANIM:
			return(Anims.Raw_Ptr(Value()));

		default:
			break;
	}
	return(0);
}


AbstractTypeClass * xTargetClass::As_TypeClass(void) const
{
	switch ((RTTIType)*this) {
		case RTTI_TEAMTYPE:
			return(TeamTypes.Raw_Ptr(Value()));

		case RTTI_TRIGGERTYPE:
			return(TriggerTypes.Raw_Ptr(Value()));

		case RTTI_BULLETTYPE:
			return((BulletTypeClass *)&BulletTypeClass::As_Reference(BulletType(Value())));

		case RTTI_OVERLAY:
			return((OverlayTypeClass *)&OverlayTypeClass::As_Reference(OverlayType(Value())));

		case RTTI_SMUDGE:
			return((SmudgeTypeClass *)&SmudgeTypeClass::As_Reference(SmudgeType(Value())));

		case RTTI_UNIT:
			return((UnitTypeClass *)&UnitTypeClass::As_Reference(UnitType(Value())));

		case RTTI_VESSEL:
			return((VesselTypeClass *)&VesselTypeClass::As_Reference(VesselType(Value())));

		case RTTI_BUILDING:
			return((BuildingTypeClass *)&BuildingTypeClass::As_Reference(StructType(Value())));

		case RTTI_INFANTRY:
			return((InfantryTypeClass *)&InfantryTypeClass::As_Reference(InfantryType(Value())));

		case RTTI_AIRCRAFT:
			return((AircraftTypeClass *)&AircraftTypeClass::As_Reference(AircraftType(Value())));

		case RTTI_TERRAIN:
			return((TerrainTypeClass *)&TerrainTypeClass::As_Reference(TerrainType(Value())));

		case RTTI_ANIM:
			return((AnimTypeClass *)&AnimTypeClass::As_Reference(AnimType(Value())));

		default:
			break;
	}
	return(0);
}


/***********************************************************************************************
 * TargetClass::As_Techno -- Converts a target into a techno object pointer.                   *
 *                                                                                             *
 *    This routine is used to convert the target object into a pointer to a techno class       *
 *    object. If the target doesn't specify a techno class object, then NULL is returned.      *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the techno class object that this target represents or   *
 *          else it returns NULL.                                                              *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   03/05/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
TechnoClass * xTargetClass::As_Techno(void) const
{
	switch ((RTTIType)*this) {
		case RTTI_UNIT:
			return(Units.Raw_Ptr(Value()));

		case RTTI_VESSEL:
			return(Vessels.Raw_Ptr(Value()));

		case RTTI_BUILDING:
			return(Buildings.Raw_Ptr(Value()));

		case RTTI_INFANTRY:
			return(Infantry.Raw_Ptr(Value()));

		case RTTI_AIRCRAFT:
			return(Aircraft.Raw_Ptr(Value()));

		default:
			break;
	}
	return(0);
}


ObjectClass * xTargetClass::As_Object(void) const
{
	switch ((RTTIType)*this) {
		case RTTI_TERRAIN:
			return(Terrains.Raw_Ptr(Value()));

		case RTTI_SMUDGE:
			return(Smudges.Raw_Ptr(Value()));

		case RTTI_OVERLAY:
			return(Overlays.Raw_Ptr(Value()));

		case RTTI_BULLET:
			return(Bullets.Raw_Ptr(Value()));

		case RTTI_ANIM:
			return(Anims.Raw_Ptr(Value()));

		case RTTI_UNIT:
			return(Units.Raw_Ptr(Value()));

		case RTTI_VESSEL:
			return(Vessels.Raw_Ptr(Value()));

		case RTTI_BUILDING:
			return(Buildings.Raw_Ptr(Value()));

		case RTTI_INFANTRY:
			return(Infantry.Raw_Ptr(Value()));

		case RTTI_AIRCRAFT:
			return(Aircraft.Raw_Ptr(Value()));

		default:
			break;
	}
	return(0);
}




/***********************************************************************************************
 * As_Target -- Converts a cell into a target value.                                           *
 *                                                                                             *
 *    This routine will convert a cell into a target value.                                    *
 *                                                                                             *
 * INPUT:   cell  -- The cell number that will be coerced into a target value.                 *
 *                                                                                             *
 * OUTPUT:  Returns with the target value that this cell represents.                           *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   03/05/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
TARGET As_Target(CELL cell)
{
	int x = Cell_X(cell);
	int y = Cell_Y(cell);

	x <<= 4;
	y <<= 4;

	x += 0x0008;
	y += 0x0008;

	return(Build_Target(RTTI_CELL, ((y << 12) | x) ));
}


/***********************************************************************************************
 * As_Target -- Converts a coordinate into a target value.                                     *
 *                                                                                             *
 *    This routine is used to convert the specified coordinate into a target value.            *
 *                                                                                             *
 * INPUT:   coord -- The coordinate that is to be converted into a target value.               *
 *                                                                                             *
 * OUTPUT:  Returns with the target value that represents the coordinate.                      *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   03/05/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
TARGET As_Target(COORDINATE coord)
{
	int x = Coord_X(coord);
	int y = Coord_Y(coord);

	x >>= 4;
	y >>= 4;

	return(Build_Target(RTTI_CELL, ((y << 12) | x) ));
}


/***********************************************************************************************
 * As_TechnoType -- Convert the target number into a techno type class pointer.                *
 *                                                                                             *
 *    This routine will conver the specified target number into a pointer to the techno        *
 *    type class that it represents.                                                           *
 *                                                                                             *
 * INPUT:   target   -- The target number to convert.                                          *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the TechnoTypeClass object that the target number        *
 *          represents. If it doesn't represent that kind of object, then NULL is returned.    *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/16/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
TechnoTypeClass const * As_TechnoType(TARGET target)
{
	int val = Target_Value(target);
	switch (Target_Kind(target)) {
		case RTTI_INFANTRYTYPE:
			return(&InfantryTypeClass::As_Reference(InfantryType(val)));

		case RTTI_UNITTYPE:
			return(&UnitTypeClass::As_Reference(UnitType(val)));

		case RTTI_VESSELTYPE:
			return(&VesselTypeClass::As_Reference(VesselType(val)));

		case RTTI_AIRCRAFTTYPE:
			return(&AircraftTypeClass::As_Reference(AircraftType(val)));

		case RTTI_BUILDINGTYPE:
			return(&BuildingTypeClass::As_Reference(StructType(val)));

	}
	return(NULL);
}


/***********************************************************************************************
 * As_TriggerType -- Convert the specified target into a trigger type.                         *
 *                                                                                             *
 *    This routine will conver the target number into a pointer to the trigger type it         *
 *    represents.                                                                              *
 *                                                                                             *
 * INPUT:   target   -- The target value to convert into a trigger type pointer.               *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the trigger type object that the specified target value  *
 *          represents. If it doesn't represent a trigger type, then NULL is returned.         *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/16/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
TriggerTypeClass * As_TriggerType(TARGET target)
{
	if (Target_Kind(target) == RTTI_TRIGGERTYPE) {
		return(TriggerTypes.Raw_Ptr(Target_Value(target)));
	}
	return(NULL);
}