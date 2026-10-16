/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef SUPER_H
#define SUPER_H

#include	"ftimer.h"

class SuperClass {
	public:
		SuperClass(NoInitClass const & x) : Control(x) {};
		SuperClass(void) : Control(NoInitClass()) {};
		SuperClass(int recharge, bool powered, VoxType charging=VOX_NONE, VoxType ready=VOX_NONE, VoxType impatient=VOX_NONE, VoxType suspend=VOX_NONE);

		bool Suspend(bool on);
		bool Enable(bool onetime = false, bool player=false, bool quiet=false);
		void Forced_Charge(bool player=false);
		bool AI(bool player=false);
		bool Remove(void);
		void Impatient_Click(void) const;
		int Anim_Stage(void) const;
		bool Discharged(bool player);
		bool Is_Ready(void) const {return(IsReady);}
		bool Is_Present(void) const {return(IsPresent);}
		bool Is_One_Time(void) const {return(IsOneTime && IsPresent);}
		bool Is_Powered(void) const {return(IsPowered);}

	private:
		bool Recharge(bool player=false);

		unsigned IsPowered:1;
		unsigned IsPresent:1;
		unsigned IsOneTime:1;
		unsigned IsReady:1;

		CDTimerClass<FrameTimerClass> Control;
		int OldStage;

		VoxType VoxRecharge;
		VoxType VoxCharging;
		VoxType VoxImpatient;
		VoxType VoxSuspend;
		int RechargeTime;

		enum {
			ANIMATION_STAGES=54
		};
};



#endif
