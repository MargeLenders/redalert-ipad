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
#include	"logic.h"
#include 	"vortex.h"

static unsigned FramesPerSecond=0;


#ifdef CHEAT_KEYS
/***********************************************************************************************
 * LogicClass::Debug_Dump -- Displays logic class status to the mono screen.                   *
 *                                                                                             *
 *    This is a debugging support routine. It displays the current state of the logic class    *
 *    to the monochrome monitor. It assumes that it is being called once per second.           *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   Call this routine only once per second.                                         *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/31/1994 JLB : Created.                                                                 *
 *   01/26/1996 JLB : Prints game time value.                                                  *
 *=============================================================================================*/
void LogicClass::Debug_Dump(MonoClass * mono) const
{
	#define RECORDCOUNT	40
	#define RECORDHEIGHT 21
	static int _framecounter = 0;

	static bool first = true;
	if (first) {
		first = false;
	mono->Set_Cursor(0, 0);
	mono->Print(Text_String(TXT_DEBUG_STRESS));
	}

//mono->Set_Cursor(0,0);mono->Printf("%d", AllowVoice);


	_framecounter++;
	mono->Set_Cursor(1, 1);mono->Printf("%ld", (long)Scen.Timer);
	mono->Set_Cursor(10, 1);mono->Printf("%3d", FramesPerSecond);
	mono->Set_Cursor(1, 3);mono->Printf("%02d:%02d:%02d", Scen.Timer / TICKS_PER_HOUR, (Scen.Timer % TICKS_PER_HOUR)/TICKS_PER_MINUTE, (Scen.Timer % TICKS_PER_MINUTE)/TICKS_PER_SECOND);

	mono->Set_Cursor(1, 11);mono->Printf("%3d", Units.Count());
	mono->Set_Cursor(1, 12);mono->Printf("%3d", Infantry.Count());
	mono->Set_Cursor(1, 13);mono->Printf("%3d", Aircraft.Count());
	mono->Set_Cursor(1, 14);mono->Printf("%3d", Vessels.Count());
	mono->Set_Cursor(1, 15);mono->Printf("%3d", Buildings.Count());
	mono->Set_Cursor(1, 16);mono->Printf("%3d", Terrains.Count());
	mono->Set_Cursor(1, 17);mono->Printf("%3d", Bullets.Count());
	mono->Set_Cursor(1, 18);mono->Printf("%3d", Anims.Count());
	mono->Set_Cursor(1, 19);mono->Printf("%3d", Teams.Count());
	mono->Set_Cursor(1, 20);mono->Printf("%3d", Triggers.Count());
	mono->Set_Cursor(1, 21);mono->Printf("%3d", TriggerTypes.Count());
	mono->Set_Cursor(1, 22);mono->Printf("%3d", Factories.Count());

	SpareTicks = min((long)SpareTicks, (long)TIMER_SECOND);

	/*
	**	CPU utilization record.
	*/
	mono->Sub_Window(15, 1, 6, 11);
	mono->Scroll();
	mono->Set_Cursor(0, 10);
	mono->Printf("%3d%%", ((TIMER_SECOND-SpareTicks)*100) / TIMER_SECOND);

	/*
	**	Update the frame rate log.
	*/
	mono->Sub_Window(22, 1, 6, 11);
	mono->Scroll();
	mono->Set_Cursor(0, 10);
	mono->Printf("%4d", FramesPerSecond);

	/*
	**	Update the findpath calc record.
	*/
	mono->Sub_Window(50, 1, 6, 11);
	mono->Scroll();
	mono->Set_Cursor(0, 10);
	mono->Printf("%4d", PathCount);
	PathCount = 0;

	/*
	**	Update the cell redraw record.
	*/
	mono->Sub_Window(29, 1, 6, 11);
	mono->Scroll();
	mono->Set_Cursor(0, 10);
	mono->Printf("%5d", CellCount);
	CellCount = 0;

	/*
	**	Update the target scan record.
	*/
	mono->Sub_Window(36, 1, 6, 11);
	mono->Scroll();
	mono->Set_Cursor(0, 10);
	mono->Printf("%5d", TargetScan);
	TargetScan = 0;

	/*
	**	Sidebar redraw record.
	*/
	mono->Sub_Window(43, 1, 6, 11);
	mono->Scroll();
	mono->Set_Cursor(0, 10);
	mono->Printf("%5d", SidebarRedraws);
	SidebarRedraws = 0;

	/*
	**	Update the CPU utilization chart.
	*/
	mono->Sub_Window(15, 13, 63, 10);
	mono->Pan(1);
	mono->Sub_Window(15, 13, 64, 10);
	int graph = RECORDHEIGHT * fixed(TIMER_SECOND-SpareTicks, TIMER_SECOND);
	for (int row = 1; row < RECORDHEIGHT; row += 2) {
		static char _barchar[4] = {' ', 220, 0, 219};
		char str[2];
		int index = 0;

		index |= (graph >= row) ? 0x01 : 0x00;
		index |= (graph >= row+1) ? 0x02: 0x00;

		str[1] = '\0';
		str[0] = _barchar[index];
		mono->Text_Print(str, 62, 9-(row/2));
	}
	mono->Sub_Window();


	SpareTicks = 0;
	FramesPerSecond = 0;
}
#endif


/***********************************************************************************************
 * LogicClass::AI -- Handles AI logic processing for game objects.                             *
 *                                                                                             *
 *    This routine is used to perform the AI processing for all game objects. This includes    *
 *    all houses, factories, objects, and teams.                                               *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/29/1994 JLB : Created.                                                                 *
 *   12/17/1994 JLB : Must perform one complete pass rather than bailing early.                *
 *   12/23/1994 JLB : Ensures that no object gets skipped if it was deleted.                   *
 *=============================================================================================*/
void LogicClass::AI(void)
{
	int index;

	FramesPerSecond++;

	/*
	** Fading to B&W or color due to the chronosphere is handled here.
	*/
	Scen.Do_Fade_AI();

	/*
	**	Handle any general timer trigger events.
	*/
	for (LogicTriggerID = 0; LogicTriggerID < LogicTriggers.Count(); LogicTriggerID++) {
		TriggerClass * trig = LogicTriggers[LogicTriggerID];

		/*
		**	Global changed trigger event might be triggered.
		*/
		if (Scen.IsGlobalChanged) {
			if (trig->Spring(TEVENT_GLOBAL_SET)) continue;
			if (trig->Spring(TEVENT_GLOBAL_CLEAR)) continue;
		}

		/*
		**	Bridge change event.
		*/
		if (Scen.IsBridgeChanged) {
			if (trig->Spring(TEVENT_ALL_BRIDGES_DESTROYED)) continue;
		}

		/*
		**	General time expire trigger events can be sprung without warning.
		*/
		if (trig->Spring(TEVENT_TIME)) continue;

		/*
		**	The mission timer expiration trigger event might spring if the timer is active
		**	but at a value of zero.
		*/
		if (Scen.MissionTimer.Is_Active() && Scen.MissionTimer == 0) {
			if (trig->Spring(TEVENT_MISSION_TIMER_EXPIRED)) continue;
		}
	}

	/*
	**	Clean up any status values that were maintained only for logic trigger
	**	purposes.
	*/
	if (Scen.MissionTimer.Is_Active() && Scen.MissionTimer == 0) {
		Scen.MissionTimer.Stop();
		Map.Flag_To_Redraw(true);			// Used only to cause tabs to redraw in new state.
	}
	Scen.IsGlobalChanged = false;
	Scen.IsBridgeChanged = false;
	/*
	**	Shadow creeping back over time is handled here.
	*/
	if (Special.IsShadowGrow && Rule.ShroudRate != 0 && Scen.ShroudTimer == 0) {
		Scen.ShroudTimer = TICKS_PER_MINUTE * Rule.ShroudRate;
		Map.Encroach_Shadow();
	}

	/*
	**	Team AI is processed.
	*/
	for (index = 0; index < Teams.Count(); index++) {
		Teams.Ptr(index)->AI();
	}

	/*
	** If there's a time quake, handle it here.
	*/
	if (TimeQuake) {
		Sound_Effect(VOC_KABOOM15);
		Shake_The_Screen(8);
	}

	ChronalVortex.AI();
	/*
	**	AI for all sentient objects is processed.
	*/
	for (index = 0; index < Count(); index++) {
		ObjectClass * obj = (*this)[index];

		BStart(BENCH_AI);
		obj->AI();
		BEnd(BENCH_AI);

		if (TimeQuake && obj != NULL && obj->IsActive && !obj->IsInLimbo && obj->Strength) {
			int damage = obj->Class_Of().MaxStrength * Rule.QuakeDamagePercent;
#ifdef FIXIT_CSII	//	checked - ajw 9/28/98
			if (TimeQuakeCenter) {
				if(::Distance(obj->As_Target(),TimeQuakeCenter)/256 < MTankDistance) {
					switch(obj->What_Am_I()) {
						case RTTI_INFANTRY:
							damage = QuakeInfantryDamage;
							break;
						case RTTI_BUILDING:
							damage = QuakeBuildingDamage * obj->Class_Of().MaxStrength;
							break;
						default:
							damage = QuakeUnitDamage * obj->Class_Of().MaxStrength;
							break;
					}
					if (damage) {
						obj->Clicked_As_Target();
						new AnimClass(ANIM_MINE_EXP1, obj->Center_Coord());
					}
					obj->Take_Damage(damage, 0, WARHEAD_AP, 0, true);
				}
			} else {
				obj->Take_Damage(damage, 0, WARHEAD_AP, 0, true);
			}
#else
			obj->Take_Damage(damage, 0, WARHEAD_AP, 0, true);
#endif
		}
		/*
		**	If the object was destroyed in the process of performing its AI, then
		**	adjust the index so that no object gets skipped.
		*/
		if (obj != (*this)[index]) {
			index--;
		}
	}
	HouseClass::Recalc_Attributes();

	/*
	**	Map related logic is performed.
	*/
	Map.Logic();

	/*
	**	Factory processing is performed.
	*/
	for (index = 0; index < Factories.Count(); index++) {
		Factories.Ptr(index)->AI();
	}

	/*
	**	House processing is performed.
	*/
#ifdef FIXIT_VERSION_3
	if( Session.Type != GAME_NORMAL )
	{
		for (HousesType house = HOUSE_MULTI1; house < HOUSE_COUNT; house++) {
			HouseClass * hptr = HouseClass::As_Pointer(house);
			if (hptr && hptr->IsActive) {
				hptr->AI();
			}
		}
	}
	else
	{
		for (HousesType house = HOUSE_FIRST; house < HOUSE_COUNT; house++) {
			HouseClass * hptr = HouseClass::As_Pointer(house);
			if (hptr && hptr->IsActive) {
				hptr->AI();
			}
		}
	}
#else	//	AI() is called redundantly 12 times in multiplayer games here. ajw
	for (HousesType house = HOUSE_FIRST; house < HOUSE_COUNT; house++) {
		HouseClass * hptr = HouseClass::As_Pointer(house);
		if (hptr && hptr->IsActive) {
			hptr->AI();
		}
	}
#endif

#ifdef FIXIT_VERSION_3			//	For endgame auto-sonar pulse.
	if( Session.Type != GAME_NORMAL && Scen.AutoSonarTimer == 0 )
	{
		if( bAutoSonarPulse )
		{
			Map.Activate_Pulse();
			Sound_Effect(VOC_SONAR);
			bAutoSonarPulse = false;
		}
#define AUTOSONAR_PERIOD	TICKS_PER_SECOND * 40;
		Scen.AutoSonarTimer = AUTOSONAR_PERIOD;
	}
#endif
}


/***********************************************************************************************
 * LogicClass::Detach -- Detatch the specified target from the logic system.                   *
 *                                                                                             *
 *    This routine is called when the specified target object is about to be removed from the  *
 *    game system and all references to it must be severed. The only thing that the logic      *
 *    system looks for in this case is to see if the target refers to a trigger and if so,     *
 *    it scans through the trigger list and removes all references to it.                      *
 *                                                                                             *
 * INPUT:   target   -- The target to remove from the sytem.                                   *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/30/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
void LogicClass::Detach(TARGET target, bool )
{
	/*
	**	Remove any triggers from the logic trigger list.
	*/
	if (Is_Target_Trigger(target)) {
		for (int index = 0; index < LogicTriggers.Count(); index++) {
			if (As_Trigger(target) == LogicTriggers[index]) {
				LogicTriggers.Delete(index);
				index--;
			}
		}
	}
}

