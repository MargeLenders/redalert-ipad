/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef TECHNO_H
#define TECHNO_H

#include	"radio.h"
#include	"stage.h"
#include	"cargo.h"
#include	"flasher.h"
#include	"house.h"
#include	"target.h"
#include	"bullet.h"
#include	"door.h"
#include	"crew.h"

/****************************************************************************
**	This is the common data between building and units.
*/
class TechnoClass :	public RadioClass,
							public FlasherClass,
							public StageClass,
							public CargoClass,
							public DoorClass
{
	public:
		CrewClass Crew;

		/*
		**	If this techno object has detected that it has outlived its
		**	purpose, then this flag will be true. Such object will either
		**	be sold or sacrificed at the first opportunity.
		*/
		unsigned IsUseless:1;

		/*
		**	This flag will be true if the object has been damaged with malice.
		**	Damage received due to friendly fire or wear and tear does not count.
		**	The computer is not allowed to sell a building unless it has been
		**	damaged with malice.
		*/
		unsigned IsTickedOff:1;

		/*
		**	If this object has inherited the ability to cloak, then this bit will
		**	be set to true.
		*/
		unsigned IsCloakable:1;

		/*
		**	If this object is designated as special then this flag will be true. For
		**	buildings, this means that it is the primary factory. For units, it means
		**	that the unit is the team leader.
		*/
		unsigned IsLeader:1;

		/*
		**	Certain units are flagged as "loaners".  These units are typically transports that
		**	are created solely for the purpose of delivering reinforcements.  Such "loaner"
		**	units are not owned by the player and thus cannot be directly controlled.  These
		**	units will leave the game as soon as they have fulfilled their purpose.
		*/
		unsigned IsALoaner:1;

		/*
		**	Once a unit enters the map, then this flag is set. This flag is used to make
		**	sure that a unit doesn't leave the map once it enters the map.
		*/
		unsigned IsLocked:1;

		/*
		**	Buildings and units with turrets usually have a recoil animation when they
		**	fire. If this flag is true, then the next rendering of the object will be
		**	in the "recoil state". The flag will then be cleared pending the next
		**	firing event.
		*/
		unsigned IsInRecoilState:1;

		/*
		**	If this unit is "loosely attached" to another unit it is given special
		**	processing. A unit is in such a condition when it is in the process of
		**	unloading from a transport type object. During the unloading process
		**	the transport object must stay still until the unit is free and clear.
		**	At that time it radios the transport object and the "tether" is broken -
		**	freeing both the unit and the transport object.
		*/
		unsigned IsTethered:1;

		/*
		**	Is this object owned by the player?  If not, then it is owned by the computer
		**	or remote opponent. This flag facilitates the many logic differences when dealing
		**	with player's or computer's units or buildings.
		*/
		unsigned IsOwnedByPlayer:1;

		/*
		**	The more sophisticated game objects must keep track of whether they are discovered
		**	or not. This is because the state of discovery can often control how the object
		**	behaves. In addition, this fact is used in radar and user I/O processing.
		*/
		unsigned IsDiscoveredByPlayer:1;

		/*
		**	This is used to control the computer recognizing this object.
		*/
		unsigned IsDiscoveredByComputer:1;

		/*
		**	Some game objects can be of the "lemon" variety. This means that they take damage
		**	even when everything is ok. This adds a little variety to the game.
		*/
		unsigned IsALemon:1;

		/*
		**	This flag is used to control second shot processing for those units or buildings
		**	that fire two shots in quick succession. When this flag is true, it indicates that
		**	the second shot is ready to fire. After this shot is fired, regular rearm timing
		**	is used rather than the short rearm time.
		*/
		unsigned IsSecondShot:1;

		/*
		**	This is the firepower and armor modifiers for this techno object. Normally,
		**	these values are fixed at 0x0100, but they can be modified by certain
		**	crate powerups.
		*/
		fixed ArmorBias;
		fixed FirepowerBias;

		/*
		**	Idle animations (if any are supported by the object type) are regulated by
		**	this timer. When the timer expires an idle animation occurs. Then the
		**	timer is reinitialized to some random (bounded) setting.
		*/
		CDTimerClass<FrameTimerClass> IdleTimer;

		/*
		** This timer keeps track of how long the unit is under the influence
		** of the iron curtain.
		*/
		CDTimerClass<FrameTimerClass> IronCurtainCountDown;


		/*
		** This is a list of bits of which houses are spying on this building,
		** if in fact this is a building.
		*/
		unsigned SpiedBy;

		/*
		**	For units in area guard mode, this is the recorded home position. The guarding
		**	unit will try to stay near this location in the course of it's maneuvers. This is
		**	also used to record a pending transport for those passengers that are waiting for
		**	the transport to become available. It is also used by harvesters so that they know
		**	where to head back to after unloading.
		*/
		TARGET ArchiveTarget;

		/*
		**	This is the house that the unit belongs to.
		*/
		CCPtr<HouseClass> House;

		/*
		**	This records the current cloak state for this vehicle.
		*/
		CloakType Cloak;
		StageClass CloakingDevice;
		CDTimerClass<FrameTimerClass> CloakDelay;

		/* (Targeting Computer)
		**	This is the target value for the item that this vehicle should ATTACK. If this
		**	is a vehicle with a turret, then it may differ from its movement destination.
		*/
		TARGET TarCom;
		TARGET SuspendedTarCom;

		/*
		**	This is the visible facing for the unit or building.
		*/
		FacingClass PrimaryFacing;

		/*
		**	This is the arming countdown. It represents the time necessary
		**	to reload the weapon.
		*/
		CDTimerClass<FrameTimerClass> Arm;

		/*
		**	The number of shot this object can fire before running out of ammo. If this
		**	value is zero, then firing is not allowed. If -1, then there is no ammunition
		**	limit.
		*/
		int Ammo;

		/*
		**	This is the amount of money spent to produce this object. This value really
		**	only comes into play for the case of buildings that have special "free"
		**	objects available when purchased at the more expensive rate.
		*/
		int PurchasePrice;

		/*---------------------------------------------------------------------
		**	Constructors, Destructors, and overloaded operators.
		*/
		TechnoClass(RTTIType rtti, int id, HousesType house=HOUSE_NONE);
#ifdef FIXIT_MULTI_SAVE
		TechnoClass(NoInitClass const & x) : RadioClass(x), FlasherClass(x), StageClass(x), CargoClass(x), DoorClass(x), IdleTimer(x), IronCurtainCountDown(x), House(x), Crew(x), CloakDelay(x), PrimaryFacing(x), Arm(x) {};
#else
		TechnoClass(NoInitClass const & x) : RadioClass(x), FlasherClass(x), StageClass(x), CargoClass(x), DoorClass(x), IronCurtainCountDown(x), House(x), Crew(x), CloakDelay(x), PrimaryFacing(x), Arm(x) {};
#endif
		virtual ~TechnoClass(void) {House=0;};

		/*
		**	Query functions.
		*/
		bool Is_Allowed_To_Retaliate(TechnoClass const * source) const;
		bool Can_Teleport_Here(CELL cell) const;
		bool Is_In_Same_Zone(CELL cell) const;
		virtual bool Is_Players_Army(void) const;
		int Combat_Damage(int which=-1) const;
		bool Is_Ready_To_Cloak(void) const;
		virtual int How_Many_Survivors(void) const;
		virtual DirType Turret_Facing(void) const {return(PrimaryFacing.Current());}
		CELL Nearby_Location(TechnoClass const * from=NULL) const;
		TechnoTypeClass * Techno_Type_Class(void) const {return((TechnoTypeClass *)&Class_Of());};
		bool Is_Visible_On_Radar(void) const;
		int Anti_Air(void) const;
		int Anti_Armor(void) const;
		int Anti_Infantry(void) const;
		int Time_To_Build(void) const;
		int What_Weapon_Should_I_Use(TARGET target) const;
		virtual ActionType What_Action(CELL cell) const;
		virtual ActionType What_Action(ObjectClass const * target) const;
		virtual BuildingClass * Find_Docking_Bay(StructType b, bool friendly) const;
		virtual CELL Find_Exit_Cell(TechnoClass const * techno) const;
		virtual COORDINATE Fire_Coord(int which) const;
		virtual DirType Desired_Load_Dir(ObjectClass * , CELL & moveto) const;
		virtual DirType Fire_Direction(void) const;
		virtual HousesType Owner(void) const;
		virtual InfantryType Crew_Type(void) const;
		virtual bool Can_Player_Fire(void) const;
		virtual bool Can_Player_Move(void) const;
		virtual bool Is_Allowed_To_Recloak(void) const;
		virtual bool Can_Repair(void) const;
		virtual bool Is_Weapon_Equipped(void) const;
		virtual fixed Tiberium_Load(void) const;
		virtual int Pip_Count(void) const;
		virtual int Rearm_Delay(bool second=true, int which=0) const;
		virtual int Refund_Amount(void) const;
		virtual int Risk(void) const;
		virtual int Threat_Range(int control) const;
		virtual int Value(void) const;
		virtual int Get_Ownable(void) const;

		/*
		**	User I/O.
		*/
		virtual void Clicked_As_Target(int count=7);
		virtual bool Select(void);
		virtual void Response_Select(void);
		virtual void Response_Move(void);
		virtual void Response_Attack(void);
		virtual void Player_Assign_Mission(MissionType order, TARGET target=TARGET_NONE, TARGET destination=TARGET_NONE);

		/*
		**	Combat related.
		*/
		fixed Area_Modify(CELL cell) const;
		virtual int Made_A_Kill(void) {return(Crew.Made_A_Kill());}
		void Base_Is_Attacked(TechnoClass const *enemy);
		void Kill_Cargo(TechnoClass * source);
		virtual void Record_The_Kill(TechnoClass * source);
		virtual bool Target_Something_Nearby(ThreatType threat=THREAT_NORMAL);
		virtual void Stun(void);
		virtual bool In_Range(COORDINATE coord, int which=0) const;
		virtual bool In_Range(TARGET target, int which=0) const;
		virtual bool In_Range(ObjectClass const * target, int which=0) const;
		virtual void Death_Announcement(TechnoClass const * source=0) const = 0;
		virtual FireErrorType Can_Fire(TARGET target, int which=0) const;
		virtual TARGET Greatest_Threat(ThreatType threat) const;
		virtual void Assign_Target(TARGET target);
		virtual void Override_Mission(MissionType mission, TARGET tarcom, TARGET navcom);
		virtual bool Restore_Mission(void);
		virtual BulletClass * Fire_At(TARGET target, int which=0);
		virtual int Weapon_Range(int which) const;
		virtual bool Captured(HouseClass * newowner);
		virtual ResultType Take_Damage(int & damage, int distance, WarheadType warhead, TechnoClass * source=0, bool forced=false);
		bool Evaluate_Cell(ThreatType method, int mask, CELL cell, int range, TechnoClass const ** object, int & value, int zone=0) const;
		bool Evaluate_Object(ThreatType method, int mask, int range, TechnoClass const * object, int & value, int zone=-1) const;
		int Evaluate_Just_Cell(CELL cell) const;
		virtual bool Electric_Zap (TARGET target, int which, COORDINATE target_coord=0L, unsigned char * remap=NULL);

		/*
		**	AI.
		*/
		virtual void Renovate(void);
		virtual void AI(void);
		virtual bool Revealed(HouseClass * house);
		virtual RadioMessageType Receive_Message(RadioClass * from, RadioMessageType message, long & param);
		void Cloaking_AI(void);

		/*
		**	Scenario and debug support.
		*/
		#ifdef CHEAT_KEYS
		virtual void Debug_Dump(MonoClass *mono) const;
		#endif

		/*
		**	File I/O.
		*/
		virtual void Code_Pointers(void);
		virtual void Decode_Pointers(void);

		/*
		**	Display and rendering support functionality. Supports imagery and how
		**	object interacts with the map and thus indirectly controls rendering.
		*/
		virtual void const * Remap_Table(void) const;
		VisualType Visual_Character(bool raw = false) const;
		void Techno_Draw_Object(void const * shapefile, int shapenum, int x, int y, WindowNumberType window, DirType rotation=DIR_N, int scale=0x0100) const;
		virtual void Draw_It(int x, int y, WindowNumberType window) const;
		virtual void Draw_Pips(int x, int y, WindowNumberType window) const;
		virtual void Hidden(void);
		virtual bool Mark(MarkType mark=MARK_CHANGE);
		virtual int Exit_Object(TechnoClass *);
		virtual void Do_Uncloak(void);
		virtual void Do_Cloak(void);
		virtual void Do_Shimmer(void);

		/*
		**	Movement and animation.
		*/
		virtual bool Is_Ready_To_Random_Animate(void) const;
		virtual bool Random_Animate(void) {return(false);}
		virtual void Assign_Destination(TARGET target);
		virtual void Per_Cell_Process(PCPType why);
		virtual void Enter_Idle_Mode(bool initial=false);
		virtual void Look(bool incremental=false);

		/*
		**	Map entry and exit logic.
		*/
		virtual bool Unlimbo(COORDINATE , DirType facing=DIR_N);
		virtual void Detach(TARGET target, bool all);

		/*
		**	Facing translation tables that fix the flaw with 3D studio when
		**	it renders 45 degree angles.
		*/
		static int const BodyShape[32];
};

#endif
