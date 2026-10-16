/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef OBJECT_H
#define OBJECT_H

#include	"abstract.h"

class ObjectClass;
class TechnoClass;
class ObjectTypeClass;
class HouseClass;
class BuildingClass;
class RadioClass;
class TriggerClass;


/**********************************************************************
**	Every game object (that can exist on the map) is ultimately derived from this object
**	class. It holds the common information between all objects. This is primarily the
**	object unique ID number and its location in the world. All common operations between
**	game objects are represented by virtual functions in this class.
*/
class ObjectClass : public AbstractClass
{
	public:
		/*
		**	The object can be in one of two states -- placed down on the map, or not. If the
		**	object is placed down on the map, then this flag will be true.
		*/
		unsigned IsDown:1;

		/*
		**	This is a support flag that is only used while building a list of objects to
		**	be damaged by a proximity affect (explosion). When this flag is set, this object
		**	will not be added to the list of units to damage. When damage is applied to the
		**	object, this flag is cleared again. This process ensures that an object is never
		**	subject to "double jeopardy".
		*/
		unsigned IsToDamage:1;

		/*
		**	Is this object flagged to be displayed during the next rendering process?  This
		**	flag could be set by many different circumstances. It is automatically cleared
		**	when the object is rerendered.
		*/
		mutable unsigned IsToDisplay:1;

		/*
		**	An object in the game may be valid yet held in a state of "limbo". Units are in such
		**	a state if they are being transported or are otherwise "inside" another unit. They can
		**	also be in limbo if they have been created but are being held until the proper time
		**	for delivery.
		*/
		unsigned IsInLimbo:1;

		/*
		**	When an object is "selected" it is given a floating bar graph or other graphic imagery
		**	to display this fact. When the player performs I/O, the actions may have a direct
		**	bearing on the actions of the currently selected object. For quick checking purposes,
		**	if this object is the one that is "selected", this flag will be true.
		*/
		unsigned IsSelected:1;

		/*
		**	If an animation is attached to this object, then this flag will be true.
		*/
		unsigned IsAnimAttached:1;

		/*
		**	If this object should process falling logic, then this flag will be true. Such
		**	objects might be ballistic projectiles, grenades, or parachuters.
		*/
		unsigned IsFalling:1;
		int Riser;

		/*
		**	Several objects could exist in the same cell list. This is a pointer to the
		**	next object in the cell list. The objects in this list are not in any
		**	significant order.
		*/
		SmartPtr<ObjectClass> Next;

		/*
		** Every object can be assigned a trigger; the same trigger can be assigned
		** to multiple objects.
		*/
		CCPtr<TriggerClass> Trigger;

		/*
		**	This is the current strength of this object.
		*/
		short Strength;

		/*-----------------------------------------------------------------------------------
		**	Constructor & destructors.
		*/
		ObjectClass(RTTIType rtti, int id);
		ObjectClass(NoInitClass const & x) : AbstractClass(x), Next(x), Trigger(x) {};
		virtual ~ObjectClass(void) {Next = 0;};
		int operator < (ObjectClass const & object) const {return Sort_Y() < object.Sort_Y();};
		int operator > (ObjectClass const & object) const {return Sort_Y() > object.Sort_Y();};

		/*
		**	Object selection control.
		*/
		static void Init(void);

		/*
		**	Query functions.
		*/
		virtual bool Is_Players_Army(void) const {return(false);}
		virtual void const * Get_Image_Data(void) const;
		virtual ActionType What_Action(ObjectClass const *) const;
		virtual ActionType What_Action(CELL) const;
		virtual LayerType In_Which_Layer(void) const;
		bool Is_Infantry(void) const {return(RTTI == RTTI_INFANTRY);};
		bool Is_Foot(void) const {return(RTTI == RTTI_INFANTRY || RTTI == RTTI_UNIT || RTTI == RTTI_VESSEL || RTTI == RTTI_AIRCRAFT);};
		bool Is_Techno(void) const {return(RTTI == RTTI_BUILDING || RTTI == RTTI_UNIT || RTTI == RTTI_INFANTRY || RTTI == RTTI_VESSEL || RTTI == RTTI_AIRCRAFT);};
		virtual int Get_Ownable(void) const;
		virtual ObjectTypeClass const & Class_Of(void) const = 0;
		virtual char const * Name(void) const;
		virtual int Full_Name(void) const;
		virtual bool Can_Repair(void) const;
		virtual bool Can_Demolish(void) const;
		virtual bool Can_Player_Fire(void) const;
		virtual bool Can_Player_Move(void) const;

		/*
		**	Coordinate inquiry functions. These are used for both display and
		**	combat purposes.
		*/
		virtual COORDINATE Docking_Coord(void) const;
		virtual COORDINATE Target_Coord(void) const;
		virtual COORDINATE Center_Coord(void) const;
		virtual COORDINATE Render_Coord(void) const;
		virtual COORDINATE Sort_Y(void) const;
		virtual COORDINATE Fire_Coord(int which) const;
		virtual COORDINATE Exit_Coord(void) const;

		/*
		**	Object entry and exit from the game system.
		*/
		virtual bool Limbo(void);
		virtual bool Unlimbo(COORDINATE , DirType facing = DIR_N);
		virtual void Detach(TARGET target, bool all=true);
		virtual void Detach_All(bool all=true);
		virtual void Record_The_Kill(TechnoClass * );
		virtual bool Paradrop(COORDINATE coord);
		bool Attach_Trigger(TriggerClass * trigger);

		/*
		**	Display and rendering support functionality. Supports imagery and how
		**	object interacts with the map and thus indirectly controls rendering.
		*/
		virtual void Do_Shimmer(void);
		virtual int Exit_Object(TechnoClass *);
		virtual bool Render(bool forced) const;
		virtual short const * Occupy_List(bool placement=false) const;
		virtual short const * Overlap_List(bool redraw=false) const;
		virtual fixed Health_Ratio(void) const;
		virtual void Draw_It(int x, int y, WindowNumberType ) const = 0;
		virtual void Hidden(void);
		virtual void Look(bool incremental=false);
		virtual bool Mark(MarkType=MARK_CHANGE);

	private:
		virtual void Mark_For_Redraw(void);

	public:

		/*
		**	User I/O.
		*/
		virtual void Active_Click_With(ActionType , ObjectClass *);
		virtual void Active_Click_With(ActionType , CELL );
		virtual void Clicked_As_Target(int = 7);
		virtual bool Select(void);
		virtual void Unselect(void);

		/*
		**	Combat related.
		*/
		virtual bool In_Range(COORDINATE , int=0) const;
		virtual int Weapon_Range(int =0) const;
		virtual ResultType Take_Damage(int & damage, int distance, WarheadType warhead, TechnoClass * source=0, bool forced=false);
		virtual void Scatter(COORDINATE , bool forced=false, bool nokidding=false);
		virtual bool Catch_Fire(void);
		virtual void Fire_Out(void);
		virtual int Value(void) const;
		virtual MissionType Get_Mission(void) const;

		/*
		**	AI.
		*/
		virtual void Per_Cell_Process(PCPType) {}
		virtual BuildingClass * Who_Can_Build_Me(bool intheory, bool legal) const;
		virtual RadioMessageType Receive_Message(RadioClass * from, RadioMessageType message, long & param);
		virtual bool Revealed(HouseClass * house);
		virtual void Repair(int );
		virtual void Sell_Back(int );
		virtual void AI(void);

		/*
		**	File I/O.
		*/
		virtual void Code_Pointers(void);
		virtual void Decode_Pointers(void);

		/*
		**	Scenario and debug support.
		*/
		#ifdef CHEAT_KEYS
		virtual void Debug_Dump(MonoClass *mono) const;
		#endif
		virtual void Move(FacingType);

		enum {FLIGHT_LEVEL=256};
};

#endif
