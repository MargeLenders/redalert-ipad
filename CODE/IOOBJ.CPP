/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#include "function.h"


/***********************************************************************************************
 * TeamTypeClass::Code_Pointers -- codes class's pointers for load/save                        *
 *                                                                                             *
 * This routine "codes" the pointers in the class by converting them to a number               *
 * that still represents the object pointed to, but isn't actually a pointer.  This            *
 * allows a saved game to properly load without relying on the games data still                *
 * being in the exact same location.                                                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void TeamTypeClass::Code_Pointers(void)
{
	/*
	**	Code the Class array
	*/
	for (int i = 0; i < ClassCount; i++) {
		Members[i].Class = (TechnoTypeClass *)Members[i].Class->As_Target();
		assert(Members[i].Class != NULL);
	}
}


/***********************************************************************************************
 * TeamTypeClass::Decode_Pointers -- decodes pointers for load/save                            *
 *                                                                                             *
 * This routine "decodes" the pointers coded in Code_Pointers by converting the                *
 * code values back into object pointers.                                                      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void TeamTypeClass::Decode_Pointers(void)
{
	/*
	**	Decode the Class array
	*/
	for (int i = 0; i < ClassCount; i++) {
		Members[i].Class =  As_TechnoType((TARGET)Members[i].Class);
		assert(Members[i].Class != NULL);
	}
}


/***********************************************************************************************
 * TeamClass::Code_Pointers -- codes class's pointers for load/save                            *
 *                                                                                             *
 * This routine "codes" the pointers in the class by converting them to a number               *
 * that still represents the object pointed to, but isn't actually a pointer.  This            *
 * allows a saved game to properly load without relying on the games data still                *
 * being in the exact same location.                                                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *   05/13/1996 JLB : Simplified.                                                              *
 *=============================================================================================*/
void TeamClass::Code_Pointers(void)
{
	/*
	**	Code the 'Member'
	*/
	if (Member) {
		Member = (FootClass *)Member->As_Target();
	}
}


/***********************************************************************************************
 * TeamClass::Decode_Pointers -- decodes pointers for load/save                                *
 *                                                                                             *
 * This routine "decodes" the pointers coded in Code_Pointers by converting the                *
 * code values back into object pointers.                                                      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *   03/12/1996 JLB : Simplified.                                                              *
 *=============================================================================================*/
void TeamClass::Decode_Pointers(void)
{
	/*
	**	Decode the 'Member'
	*/
	if (Member) {
		Member = (FootClass *)As_Techno((TARGET)Member);
		assert(Member != NULL);
	}
}


/***********************************************************************************************
 * TriggerClass::Code_Pointers -- codes class's pointers for load/save                         *
 *                                                                                             *
 * This routine "codes" the pointers in the class by converting them to a number               *
 * that still represents the object pointed to, but isn't actually a pointer.  This            *
 * allows a saved game to properly load without relying on the games data still                *
 * being in the exact same location.                                                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void TriggerTypeClass::Code_Pointers(void)
{
	Action1.Code_Pointers();
	Action2.Code_Pointers();
}


/***********************************************************************************************
 * TriggerClass::Decode_Pointers -- decodes pointers for load/save                             *
 *                                                                                             *
 * This routine "decodes" the pointers coded in Code_Pointers by converting the                *
 * code values back into object pointers.                                                      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void TriggerTypeClass::Decode_Pointers(void)
{
	Action1.Decode_Pointers();
	Action2.Decode_Pointers();
}


/***********************************************************************************************
 * BulletClass::Code_Pointers -- codes class's pointers for load/save                          *
 *                                                                                             *
 * This routine "codes" the pointers in the class by converting them to a number               *
 * that still represents the object pointed to, but isn't actually a pointer.  This            *
 * allows a saved game to properly load without relying on the games data still                *
 * being in the exact same location.                                                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void BulletClass::Code_Pointers(void)
{
	/*
	**	Code 'Payback'
	*/
	if (Payback) {
		Payback = (TechnoClass *)Payback->As_Target();
	}

	/*
	**	Chain to parent
	*/
	ObjectClass::Code_Pointers();
}


/***********************************************************************************************
 * BulletClass::Decode_Pointers -- decodes pointers for load/save                              *
 *                                                                                             *
 * This routine "decodes" the pointers coded in Code_Pointers by converting the                *
 * code values back into object pointers.                                                      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void BulletClass::Decode_Pointers(void)
{
	/*
	**	Decode 'Payback'
	*/
	if (Payback) {
		Payback = As_Techno((TARGET)Payback);
		assert(Payback != NULL);
	}

	/*
	**	Chain to parent
	*/
	ObjectClass::Decode_Pointers();
}


/***********************************************************************************************
 * FactoryClass::Code_Pointers -- codes class's pointers for load/save                         *
 *                                                                                             *
 * This routine "codes" the pointers in the class by converting them to a number               *
 * that still represents the object pointed to, but isn't actually a pointer.  This            *
 * allows a saved game to properly load without relying on the games data still                *
 * being in the exact same location.                                                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void FactoryClass::Code_Pointers(void)
{
	if (Object) {
		Object = (TechnoClass *)Object->As_Target();
	}

	((HouseClass *&)House) = (HouseClass *)House->Class->House;
}


/***********************************************************************************************
 * FactoryClass::Decode_Pointers -- decodes pointers for load/save                             *
 *                                                                                             *
 * This routine "decodes" the pointers coded in Code_Pointers by converting the                *
 * code values back into object pointers.                                                      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void FactoryClass::Decode_Pointers(void)
{
	if (Object) {
		Object = As_Techno((TARGET)Object);
		assert(Object != NULL);
	}

	((HouseClass *&)House) = HouseClass::As_Pointer((HousesType)(intptr_t)House);
	assert(House != NULL);
}


/***********************************************************************************************
 * LayerClass::Load -- Loads from a save game file.                                            *
 *                                                                                             *
 * INPUT:   file  -- The file to read the cell's data from.                                    *
 *                                                                                             *
 * OUTPUT:  true = success, false = failure                                                    *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09/19/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
bool LayerClass::Load(Straw & file)
{
	/*
	**	Read # elements in the layer
	*/
	int count;
	if (file.Get(&count, sizeof(count)) != sizeof(count)) {
		return(false);
	}

	/*
	**	Clear the array
	*/
	Clear();

	/*
	**	Read in all array elements
	*/
	for (int index = 0; index < count; index++) {
		ObjectClass * ptr;
		if (file.Get(&ptr, sizeof(ObjectClass *)) != sizeof(ObjectClass *)) {
			return(false);
		}
		Add(ptr);
	}

	return(true);
}


/***********************************************************************************************
 * LayerClass::Save -- Write to a save game file.                                              *
 *                                                                                             *
 * INPUT:   file  -- The file to write the cell's data to.                                     *
 *                                                                                             *
 * OUTPUT:  true = success, false = failure                                                    *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09/19/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
bool LayerClass::Save(Pipe & file) const
{
	/*
	**	Save # array elements
	*/
	int count = Count();
	file.Put(&count, sizeof(count));

	/*
	**	Save all elements
	*/
	for (int index = 0; index < count; index++) {
		ObjectClass * ptr = (*this)[index];
		file.Put(&ptr, sizeof(ObjectClass *));
	}

	return(true);
}


/***********************************************************************************************
 * LayerClass::Code_Pointers -- codes class's pointers for load/save                           *
 *                                                                                             *
 * This routine "codes" the pointers in the class by converting them to a number               *
 * that still represents the object pointed to, but isn't actually a pointer.  This            *
 * allows a saved game to properly load without relying on the games data still                *
 * being in the exact same location.                                                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void LayerClass::Code_Pointers(void)
{
	for (int index = 0; index < Count(); index++) {
		ObjectClass * obj = (*this)[index];
		assert(obj != NULL);
		(*this)[index] = (ObjectClass *)(obj->As_Target());
	}
}


/***********************************************************************************************
 * LayerClass::Decode_Pointers -- decodes pointers for load/save                               *
 *                                                                                             *
 * This routine "decodes" the pointers coded in Code_Pointers by converting the                *
 * code values back into object pointers.                                                      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void LayerClass::Decode_Pointers(void)
{
	for (int index = 0; index < Count(); index++) {
		TARGET target = (TARGET)(*this)[index];
		(*this)[index] = (ObjectClass *)As_Object(target);
		assert((*this)[index] != NULL);
	}
}


/***********************************************************************************************
 * HouseClass::Code_Pointers -- codes class's pointers for load/save                           *
 *                                                                                             *
 * This routine "codes" the pointers in the class by converting them to a number               *
 * that still represents the object pointed to, but isn't actually a pointer.  This            *
 * allows a saved game to properly load without relying on the games data still                *
 * being in the exact same location.                                                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void HouseClass::Code_Pointers(void)
{
}


/***********************************************************************************************
 * HouseClass::Decode_Pointers -- decodes pointers for load/save                               *
 *                                                                                             *
 * This routine "decodes" the pointers coded in Code_Pointers by converting the                *
 * code values back into object pointers.                                                      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void HouseClass::Decode_Pointers(void)
{
	/*
	** Re-assign the house's remap table (for multiplayer game loads)
	** Loading the house from disk will have over-written the house's RemapTable, so
	** Init_Data() is called to reset it to a valid pointer.
	*/
	Init_Data(RemapColor, ActLike, Credits);
}


/***********************************************************************************************
 * ScoreClass::Code_Pointers -- codes class's pointers for load/save                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void ScoreClass::Code_Pointers(void)
{
	RealTime.Stop();
}


/***********************************************************************************************
 * ScoreClass::Decode_Pointers -- decodes pointers for load/save                               *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void ScoreClass::Decode_Pointers(void)
{
	RealTime.Start();
}


/***********************************************************************************************
 * FootClass::Code_Pointers -- codes class's pointers for load/save                            *
 *                                                                                             *
 * This routine "codes" the pointers in the class by converting them to a number               *
 * that still represents the object pointed to, but isn't actually a pointer.  This            *
 * allows a saved game to properly load without relying on the games data still                *
 * being in the exact same location.                                                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void FootClass::Code_Pointers(void)
{
	if (Member != NULL && Member->IsActive) {
		Member = (FootClass *)Member->As_Target();
	} else {
		Member = TARGET_NONE;
	}

	TechnoClass::Code_Pointers();
}


/***********************************************************************************************
 * FootClass::Decode_Pointers -- decodes pointers for load/save                                *
 *                                                                                             *
 * This routine "decodes" the pointers coded in Code_Pointers by converting the                *
 * code values back into object pointers.                                                      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void FootClass::Decode_Pointers(void)
{
	if ((TARGET)Member != TARGET_NONE) {
		Member = (FootClass *)As_Techno((TARGET)Member);
		assert(Member != NULL);
	}

	TechnoClass::Decode_Pointers();
}


/***********************************************************************************************
 * RadioClass::Code_Pointers -- codes class's pointers for load/save                           *
 *                                                                                             *
 * This routine "codes" the pointers in the class by converting them to a number               *
 * that still represents the object pointed to, but isn't actually a pointer.  This            *
 * allows a saved game to properly load without relying on the games data still                *
 * being in the exact same location.                                                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void RadioClass::Code_Pointers(void)
{
	/*
	**	Code 'Radio'
	*/
	if (Radio) {
		Radio = (RadioClass *)Radio->As_Target();
	}

	MissionClass::Code_Pointers();
}


/***********************************************************************************************
 * RadioClass::Decode_Pointers -- decodes pointers for load/save                               *
 *                                                                                             *
 * This routine "decodes" the pointers coded in Code_Pointers by converting the                *
 * code values back into object pointers.                                                      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void RadioClass::Decode_Pointers(void)
{
	/*
	**	Decode 'Radio'
	*/
	if (Radio) {
		Radio = As_Techno((TARGET)Radio);
		assert(Radio != NULL);
	}

	MissionClass::Decode_Pointers();
}


/***********************************************************************************************
 * TechnoClass::Code_Pointers -- codes class's pointers for load/save                          *
 *                                                                                             *
 * This routine "codes" the pointers in the class by converting them to a number               *
 * that still represents the object pointed to, but isn't actually a pointer.  This            *
 * allows a saved game to properly load without relying on the games data still                *
 * being in the exact same location.                                                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void TechnoClass::Code_Pointers(void)
{
	CargoClass::Code_Pointers();
	RadioClass::Code_Pointers();
}


/***********************************************************************************************
 * TechnoClass::Decode_Pointers -- decodes pointers for load/save                              *
 *                                                                                             *
 * This routine "decodes" the pointers coded in Code_Pointers by converting the                *
 * code values back into object pointers.                                                      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void TechnoClass::Decode_Pointers(void)
{
	CargoClass::Decode_Pointers();
	RadioClass::Decode_Pointers();
}


/***********************************************************************************************
 * CargoClass::Code_Pointers -- codes class's pointers for load/save                           *
 *                                                                                             *
 * This routine "codes" the pointers in the class by converting them to a number               *
 * that still represents the object pointed to, but isn't actually a pointer.  This            *
 * allows a saved game to properly load without relying on the games data still                *
 * being in the exact same location.                                                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void CargoClass::Code_Pointers(void)
{
	/*
	**	Code 'CargoHold'
	*/
	if (CargoHold) {
		CargoHold = (FootClass *)CargoHold->As_Target();
	}
}


/***********************************************************************************************
 * CargoClass::Decode_Pointers -- decodes pointers for load/save                               *
 *                                                                                             *
 * This routine "decodes" the pointers coded in Code_Pointers by converting the                *
 * code values back into object pointers.                                                      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void CargoClass::Decode_Pointers(void)
{
	/*
	**	Decode 'CargoHold'
	*/
	if (CargoHold) {
		CargoHold = (FootClass *)As_Techno((TARGET)CargoHold);
		assert(CargoHold != NULL);
	}
}


/***********************************************************************************************
 * ObjectClass::Code_Pointers -- codes class's pointers for load/save                          *
 *                                                                                             *
 * This routine "codes" the pointers in the class by converting them to a number               *
 * that still represents the object pointed to, but isn't actually a pointer.  This            *
 * allows a saved game to properly load without relying on the games data still                *
 * being in the exact same location.                                                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void ObjectClass::Code_Pointers(void)
{
	if (Next) {
		Next = (ObjectClass *)Next->As_Target();
	}
}


/***********************************************************************************************
 * ObjectClass::Decode_Pointers -- decodes pointers for load/save                              *
 *                                                                                             *
 * This routine "decodes" the pointers coded in Code_Pointers by converting the                *
 * code values back into object pointers.                                                      *
 *                                                                                             *
 * INPUT:                                                                                      *
 *      none.                                                                                  *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *      none.                                                                                  *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *      none.                                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/02/1995 BR : Created.                                                                  *
 *=============================================================================================*/
void ObjectClass::Decode_Pointers(void)
{
	if (Next) {
		Next = As_Object((TARGET)Next);
		assert(Next != NULL);
	}
}
