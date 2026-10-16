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


/***********************************************************************************************
 * SuperClass::SuperClass -- Constructor for special super weapon objects.                     *
 *                                                                                             *
 *    This is the constructor for the super weapons.                                           *
 *                                                                                             *
 * INPUT:   recharge    -- The recharge delay time (in game frames).                           *
 *                                                                                             *
 *          charging    -- Voice to announce that the weapon is charging.                      *
 *                                                                                             *
 *          ready       -- Voice to announce that the weapon is fully charged.                 *
 *                                                                                             *
 *          impatient   -- Voice to announce current charging state.                           *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/28/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
SuperClass::SuperClass(int recharge, bool powered, VoxType charging, VoxType ready, VoxType impatient, VoxType suspend) :
	IsPowered(powered),
	IsPresent(false),
	IsOneTime(false),
	IsReady(false),
	Control(0),
	OldStage(-1),
	VoxRecharge(ready),
	VoxCharging(charging),
	VoxImpatient(impatient),
	VoxSuspend(suspend),
	RechargeTime(recharge)
{
}


/***********************************************************************************************
 * SuperClass::Suspend -- Suspend the charging of the super weapon.                            *
 *                                                                                             *
 *    This will temporarily put on hold the charging of the special weapon. This might be the  *
 *    result of insufficient power.                                                            *
 *                                                                                             *
 * INPUT:   on -- Should the weapon charging be suspended? Else, it will unsuspend.            *
 *                                                                                             *
 * OUTPUT:  Was the weapon suspend state changed?                                              *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/28/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
bool SuperClass::Suspend(bool on)
{
	if (IsPresent && !IsReady && !IsOneTime && on == Control.Is_Active()) {
		if (!on) {
			Control.Start();
		} else {
			Control.Stop();
		}
//		if (on != IsSuspended) {
//			if (on) {
//				SuspendTime = Control;
//			} else {
//				Control = SuspendTime;
//			}
//			IsSuspended = on;
			return(true);
//		}
	}
	return(false);
}


/***********************************************************************************************
 * SuperClass::Enable -- Enable this super special weapon.                                     *
 *                                                                                             *
 *    This routine is called when the special weapon needs to be activated. This is used for   *
 *    both the normal super weapons and the special one-time super weapons (from crates).      *
 *                                                                                             *
 * INPUT:   onetime  -- Is this a special one time super weapon?                               *
 *                                                                                             *
 *          player   -- Is this weapon for the player? If true, then there might be a voice    *
 *                      announcement of this weapon's availability.                            *
 *                                                                                             *
 *          quiet    -- Request that the weapon start in suspended state (quiet mode).         *
 *                                                                                             *
 * OUTPUT:  Was the special super weapon enabled? Failure might indicate that the weapon was   *
 *          already available.                                                                 *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/28/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
bool SuperClass::Enable(bool onetime, bool player, bool quiet)
{
	if (!IsPresent) {
		IsPresent = true;
		IsOneTime = onetime;
		bool retval = Recharge(player && !quiet);
		if (quiet) Suspend(true);
		return(retval);
	}
	return(false);
}


/***********************************************************************************************
 * SuperClass::Remove -- Removes super weapon availability.                                    *
 *                                                                                             *
 *    Call this routine when the super weapon should be removed because of some outside        *
 *    force. For one time special super weapons, they can never be removed except as the       *
 *    result of discharging them.                                                              *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  Was the special weapon removed and disabled?                                       *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/28/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
bool SuperClass::Remove(void)
{
	if (IsPresent && !IsOneTime) {
		IsReady = false;
		IsPresent = false;
		return(true);
	}
	return(false);
}


/***********************************************************************************************
 * SuperClass::Recharge -- Starts the special super weapon recharging.                         *
 *                                                                                             *
 *    This routine is called when the special weapon is allowed to recharge. Suspension will   *
 *    be disabled and the animation process will begin.                                        *
 *                                                                                             *
 * INPUT:   player   -- Is this for a player owned super weapon? If so, then a voice           *
 *                      announcement might be in order.                                        *
 *                                                                                             *
 * OUTPUT:  Was the super weapon begun charging up?                                            *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/28/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
bool SuperClass::Recharge(bool player)
{
	if (IsPresent && !IsReady) {
//		IsSuspended = false;
		OldStage = -1;
		Control.Start();
		Control = RechargeTime;

#ifdef CHEAT_KEYS
		if (Special.IsSpeedBuild) {
			Control = 1;
		}
#endif

		if (player) {
			Speak(VoxCharging);
		}
		return(true);
	}
	return(false);
}


/***********************************************************************************************
 * Superclass::Discharged -- Handles discharged action for special super weapon.               *
 *                                                                                             *
 *    This routine should be called when the special super weapon has been discharged. The     *
 *    weapon will either begin charging anew or will be removed entirely -- depends on the     *
 *    one time flag for the weapon.                                                            *
 *                                                                                             *
 * INPUT:   player   -- Is this special weapon for the player? If so, then there might be a    *
 *                      voice announcement.                                                    *
 *                                                                                             *
 * OUTPUT:  Should the sidebar be reprocessed because the special weapon has been eliminated?  *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/28/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
bool SuperClass::Discharged(bool player)
{
	if (Control.Is_Active() && IsPresent && IsReady) {
		IsReady = false;
		if (IsOneTime) {
			IsOneTime = false;
			return(Remove());
		} else {
			Recharge(player);
		}
	}
	return(false);
}


/***********************************************************************************************
 * SuperClass::AI -- Process the super weapon AI.                                              *
 *                                                                                             *
 *    This routine will process the charge up AI for this super weapon object. If the weapon   *
 *    has advanced far enough to change any sidebar graphic that might represent it, then      *
 *    "true" will be returned. Use this return value to intelligently update the sidebar.      *
 *                                                                                             *
 * INPUT:   player   -- Is this for the player? If it is and the weapon is now fully charged,  *
 *                      then this fully charged state will be announced to the player.         *
 *                                                                                             *
 * OUTPUT:  Was the weapon's state changed such that a sidebar graphic update will be          *
 *          necessary?                                                                         *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/28/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
bool SuperClass::AI(bool player)
{
	if (IsPresent && !IsReady) {
		if (!Control.Is_Active()) {
			if (OldStage != -1) {
				OldStage = -1;
				return(true);
			}
		} else {
			if (Control == 0) {
				IsReady = true;
				if (player) {
					Speak(VoxRecharge);
				}
				return(true);
			} else {
				if (Anim_Stage() != OldStage) {
					OldStage = Anim_Stage();
					return(true);
				}
			}
		}
	}
	return(false);
}


/***********************************************************************************************
 * SuperClass::Anim_Stage -- Fetches the animation stage for this super weapon.                *
 *                                                                                             *
 *    This will return the current animation stage for this super weapon. The value will be    *
 *    between zero (uncharged) to ANIMATION_STAGES (fully charged). Use this value to render   *
 *    the appropriate graphic on the sidebar.                                                  *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  Returns with the current animation stage for this special super weapon powerup.    *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/28/1995 JLB : Created.                                                                 *
 *   10/11/1996 JLB : Doesn't show complete until really complete.                             *
 *=============================================================================================*/
int SuperClass::Anim_Stage(void) const
{
	if (IsPresent) {
		if (IsReady) {
			return(ANIMATION_STAGES);
		}
//		int time = Control;
//		if (IsSuspended) {
//			time = SuspendTime;
//		}

		int stage = ANIMATION_STAGES * fixed(RechargeTime-Control.Value(), RechargeTime);
		stage = min(stage, ANIMATION_STAGES-1);
		return(stage);
	}
	return(0);
}


/***********************************************************************************************
 * SuperClass::Impatient_Click -- Called when player clicks on unfinished super weapon.        *
 *                                                                                             *
 *    This routine is called when the player clicks on the super weapon icon on the sidebar    *
 *    when the super weapon is not ready yet. This results in a voice message feedback to the  *
 *    player.                                                                                  *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/28/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
void SuperClass::Impatient_Click(void) const
{
	if (!Control.Is_Active()) {
		Speak(VoxSuspend);
	} else {
		Speak(VoxImpatient);
	}
}


/***********************************************************************************************
 * SuperClass::Forced_Charge -- Force the super weapon to full charge state.                   *
 *                                                                                             *
 *    This routine will force the special weapon to full charge state. Call it when the weapon *
 *    needs to be instantly charged. The airstrike (when it first becomes available) is a      *
 *    good example.                                                                            *
 *                                                                                             *
 * INPUT:   player   -- Is this for the player? If true, then the full charge state will be    *
 *                      announced.                                                             *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/29/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
void SuperClass::Forced_Charge(bool player)
{
	if (IsPresent) {
		IsReady = true;
		Control.Start();
		Control = 0;
//		IsSuspended = false;
		if (player) {
			Speak(VoxRecharge);
		}
	}
}
