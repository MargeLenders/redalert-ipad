#ifndef MOBILE_TOUCH_HUD_H
#define MOBILE_TOUCH_HUD_H

#include "windows.h"

enum MobileTouchHudButtonId {
	HUD_BTN_NONE = -1,
	HUD_BTN_TOGGLE = 0,
	HUD_BTN_FORCE_ATTACK,
	HUD_BTN_GROUP_1,
	HUD_BTN_GROUP_2,
	HUD_BTN_GROUP_3,
	HUD_BTN_GROUP_4,
	HUD_BTN_STOP,
	HUD_BTN_SCATTER,
	HUD_BTN_COUNT
};

enum MobileTouchHudActionType {
	HUD_ACTION_NONE = 0,
	HUD_ACTION_FORCE_ATTACK_CHANGED,
	HUD_ACTION_GROUP_SELECT,
	HUD_ACTION_GROUP_ASSIGN,
	HUD_ACTION_GROUP_CENTER,
	HUD_ACTION_KEY_PULSE
};

struct MobileTouchHudAction {
	MobileTouchHudActionType type;
	int vk;
	int param;
};

struct MobileTouchHUD {
	int collapsed;
	int active_button;
	long long active_finger;
	int finger_inside;
	unsigned long down_tick;
	int long_press_triggered;
	int force_attack_held;
	int force_attack_latched;
	int group_assigned[4];
	unsigned long last_group_tap_tick[4];
	int last_tapped_group;
};

static inline void MobileTouchHud_Init(MobileTouchHUD *hud)
{
	if (!hud) return;
	hud->collapsed = 0;
	hud->active_button = HUD_BTN_NONE;
	hud->active_finger = 0;
	hud->finger_inside = 0;
	hud->down_tick = 0;
	hud->long_press_triggered = 0;
	hud->force_attack_held = 0;
	hud->force_attack_latched = 0;
	for (int i = 0; i < 4; ++i) {
		hud->group_assigned[i] = 0;
		hud->last_group_tap_tick[i] = 0;
	}
	hud->last_tapped_group = -1;
}

static inline int MobileTouchHud_GetButtonRect(
	MobileTouchHUD const *hud,
	int button_id,
	int *x,
	int *y,
	int *w,
	int *h)
{
	if (!hud) return 0;

	if (hud->collapsed) {
		if (button_id == HUD_BTN_TOGGLE) {
			if (x) *x = 2;
			if (y) *y = 32;
			if (w) *w = 20;
			if (h) *h = 22;
			return 1;
		}
		return 0;
	}

	int bx = 4;
	int bw = 28;
	int by = 0;
	int bh = 24;

	switch (button_id) {
		case HUD_BTN_TOGGLE:
			by = 24;
			bh = 18;
			break;
		case HUD_BTN_FORCE_ATTACK:
			by = 46;
			bh = 26;
			break;
		case HUD_BTN_GROUP_1:
			by = 76;
			bh = 24;
			break;
		case HUD_BTN_GROUP_2:
			by = 104;
			bh = 24;
			break;
		case HUD_BTN_GROUP_3:
			by = 132;
			bh = 24;
			break;
		case HUD_BTN_GROUP_4:
			by = 160;
			bh = 24;
			break;
		case HUD_BTN_STOP:
			by = 188;
			bh = 22;
			break;
		case HUD_BTN_SCATTER:
			by = 214;
			bh = 22;
			break;
		default:
			return 0;
	}

	if (x) *x = bx;
	if (y) *y = by;
	if (w) *w = bw;
	if (h) *h = bh;
	return 1;
}

static inline int MobileTouchHud_HitTest(MobileTouchHUD const *hud, int x, int y)
{
	if (!hud) return HUD_BTN_NONE;

	if (hud->collapsed) {
		int bx, by, bw, bh;
		if (MobileTouchHud_GetButtonRect(hud, HUD_BTN_TOGGLE, &bx, &by, &bw, &bh)) {
			static const int slop = 4;
			if (x >= bx - slop && x < bx + bw + slop && y >= by - slop && y < by + bh + slop) {
				return HUD_BTN_TOGGLE;
			}
		}
		return HUD_BTN_NONE;
	}

	static const int slop = 3;
	for (int id = 0; id < HUD_BTN_COUNT; ++id) {
		int bx, by, bw, bh;
		if (MobileTouchHud_GetButtonRect(hud, id, &bx, &by, &bw, &bh)) {
			if (x >= bx - slop && x < bx + bw + slop && y >= by - slop && y < by + bh + slop) {
				return id;
			}
		}
	}
	return HUD_BTN_NONE;
}

static inline int MobileTouchHud_IsFingerActive(MobileTouchHUD const *hud, long long finger)
{
	return hud && hud->active_button != HUD_BTN_NONE && hud->active_finger == finger;
}

static inline int MobileTouchHud_IsForceAttackActive(MobileTouchHUD const *hud)
{
	return hud && (hud->force_attack_held || hud->force_attack_latched);
}

static inline void MobileTouchHud_ClearForceAttackLatch(MobileTouchHUD *hud)
{
	if (hud) {
		hud->force_attack_latched = 0;
	}
}

static inline void MobileTouchHud_FingerDown(
	MobileTouchHUD *hud,
	long long finger,
	int x,
	int y,
	unsigned long tick,
	MobileTouchHudAction *action)
{
	if (action) {
		action->type = HUD_ACTION_NONE;
		action->vk = 0;
		action->param = 0;
	}
	if (!hud) return;

	int hit = MobileTouchHud_HitTest(hud, x, y);
	if (hit == HUD_BTN_NONE) return;

	hud->active_button = hit;
	hud->active_finger = finger;
	hud->finger_inside = 1;
	hud->down_tick = tick;
	hud->long_press_triggered = 0;

	if (hit == HUD_BTN_FORCE_ATTACK) {
		hud->force_attack_held = 1;
		if (action) {
			action->type = HUD_ACTION_FORCE_ATTACK_CHANGED;
		}
	}
}

static inline void MobileTouchHud_FingerMove(MobileTouchHUD *hud, long long finger, int x, int y)
{
	if (!hud || hud->active_button == HUD_BTN_NONE || hud->active_finger != finger) {
		return;
	}
	int hit = MobileTouchHud_HitTest(hud, x, y);
	hud->finger_inside = (hit == hud->active_button);
}

static inline void MobileTouchHud_Update(MobileTouchHUD *hud, unsigned long tick, MobileTouchHudAction *action)
{
	if (action) {
		action->type = HUD_ACTION_NONE;
		action->vk = 0;
		action->param = 0;
	}
	if (!hud || hud->active_button == HUD_BTN_NONE || !hud->finger_inside || hud->long_press_triggered) {
		return;
	}

	static const unsigned long long_press_ms = 350;
	if (tick >= hud->down_tick && (tick - hud->down_tick >= long_press_ms)) {
		int btn = hud->active_button;
		if (btn >= HUD_BTN_GROUP_1 && btn <= HUD_BTN_GROUP_4) {
			int group_idx = btn - HUD_BTN_GROUP_1;
			hud->long_press_triggered = 1;
			hud->group_assigned[group_idx] = 1;
			if (action) {
				action->type = HUD_ACTION_GROUP_ASSIGN;
				action->param = group_idx;
				action->vk = VK_1 + group_idx;
			}
		}
	}
}

static inline void MobileTouchHud_FingerUp(
	MobileTouchHUD *hud,
	long long finger,
	int x,
	int y,
	unsigned long tick,
	MobileTouchHudAction *action)
{
	if (action) {
		action->type = HUD_ACTION_NONE;
		action->vk = 0;
		action->param = 0;
	}
	if (!hud || hud->active_button == HUD_BTN_NONE || hud->active_finger != finger) {
		return;
	}

	int btn = hud->active_button;
	int inside = hud->finger_inside || (MobileTouchHud_HitTest(hud, x, y) == btn);
	unsigned long duration = (tick >= hud->down_tick) ? (tick - hud->down_tick) : 0;
	int was_long_press = hud->long_press_triggered;

	hud->active_button = HUD_BTN_NONE;
	hud->active_finger = 0;
	hud->finger_inside = 0;
	hud->long_press_triggered = 0;

	if (btn == HUD_BTN_FORCE_ATTACK) {
		hud->force_attack_held = 0;
		if (inside && duration < 300) {
			hud->force_attack_latched = !hud->force_attack_latched;
		}
		if (action) {
			action->type = HUD_ACTION_FORCE_ATTACK_CHANGED;
		}
		return;
	}

	if (!inside) {
		return;
	}

	if (btn == HUD_BTN_TOGGLE) {
		hud->collapsed = !hud->collapsed;
		return;
	}

	if (btn >= HUD_BTN_GROUP_1 && btn <= HUD_BTN_GROUP_4) {
		int group_idx = btn - HUD_BTN_GROUP_1;
		if (was_long_press) {
			return;
		}
		if (duration >= 350) {
			hud->group_assigned[group_idx] = 1;
			if (action) {
				action->type = HUD_ACTION_GROUP_ASSIGN;
				action->param = group_idx;
				action->vk = VK_1 + group_idx;
			}
			return;
		}

		static const unsigned long double_tap_ms = 400;
		if (hud->last_tapped_group == group_idx &&
			hud->last_group_tap_tick[group_idx] > 0 &&
			tick >= hud->last_group_tap_tick[group_idx] &&
			(tick - hud->last_group_tap_tick[group_idx] <= double_tap_ms)) {
			hud->last_group_tap_tick[group_idx] = 0;
			if (action) {
				action->type = HUD_ACTION_GROUP_CENTER;
				action->param = group_idx;
				action->vk = VK_1 + group_idx;
			}
		} else {
			hud->last_group_tap_tick[group_idx] = tick;
			hud->last_tapped_group = group_idx;
			if (action) {
				action->type = HUD_ACTION_GROUP_SELECT;
				action->param = group_idx;
				action->vk = VK_1 + group_idx;
			}
		}
		return;
	}

	if (btn == HUD_BTN_STOP) {
		if (action) {
			action->type = HUD_ACTION_KEY_PULSE;
			action->vk = VK_S;
		}
		return;
	}

	if (btn == HUD_BTN_SCATTER) {
		if (action) {
			action->type = HUD_ACTION_KEY_PULSE;
			action->vk = 0x58; // VK_X
		}
		return;
	}
}

static inline void MobileTouchHud_OnAttackFired(MobileTouchHUD *hud, MobileTouchHudAction *action)
{
	if (action) {
		action->type = HUD_ACTION_NONE;
		action->vk = 0;
		action->param = 0;
	}
	if (hud && hud->force_attack_latched) {
		hud->force_attack_latched = 0;
		if (action) {
			action->type = HUD_ACTION_FORCE_ATTACK_CHANGED;
		}
	}
}

static inline void MobileTouchHud_Cancel(MobileTouchHUD *hud, MobileTouchHudAction *action)
{
	if (action) {
		action->type = HUD_ACTION_NONE;
		action->vk = 0;
		action->param = 0;
	}
	if (!hud) return;
	int had_attack = MobileTouchHud_IsForceAttackActive(hud);
	hud->active_button = HUD_BTN_NONE;
	hud->active_finger = 0;
	hud->finger_inside = 0;
	hud->long_press_triggered = 0;
	hud->force_attack_held = 0;
	hud->force_attack_latched = 0;
	if (had_attack && action) {
		action->type = HUD_ACTION_FORCE_ATTACK_CHANGED;
	}
}

#endif
