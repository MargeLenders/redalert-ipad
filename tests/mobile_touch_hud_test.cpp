#include "mobile_touch_hud.h"
#include "mobile_key_message.h"

#include <assert.h>

static void test_initial_state(void)
{
	MobileTouchHUD hud;
	MobileTouchHud_Init(&hud);
	assert(!hud.collapsed);
	assert(hud.active_button == HUD_BTN_NONE);
	assert(!MobileTouchHud_IsForceAttackActive(&hud));
	for (int i = 0; i < 4; ++i) {
		assert(hud.group_assigned[i] == 0);
	}
}

static void test_collapse_and_expand(void)
{
	MobileTouchHUD hud;
	MobileTouchHud_Init(&hud);
	MobileTouchHudAction action;

	// Tap toggle to collapse
	MobileTouchHud_FingerDown(&hud, 1, 6, 26, 1000, &action);
	assert(hud.active_button == HUD_BTN_TOGGLE);
	MobileTouchHud_FingerUp(&hud, 1, 6, 26, 1050, &action);
	assert(hud.collapsed == 1);

	// When collapsed, only toggle button responds to hit test
	assert(MobileTouchHud_HitTest(&hud, 6, 36) == HUD_BTN_TOGGLE);
	assert(MobileTouchHud_HitTest(&hud, 6, 80) == HUD_BTN_NONE);
	assert(MobileTouchHud_HitTest(&hud, 6, 120) == HUD_BTN_NONE);

	// Tap toggle to expand
	MobileTouchHud_FingerDown(&hud, 1, 6, 36, 1100, &action);
	assert(hud.active_button == HUD_BTN_TOGGLE);
	MobileTouchHud_FingerUp(&hud, 1, 6, 36, 1150, &action);
	assert(hud.collapsed == 0);

	// Now other buttons hit test again
	assert(MobileTouchHud_HitTest(&hud, 6, 50) == HUD_BTN_FORCE_ATTACK);
	assert(MobileTouchHud_HitTest(&hud, 6, 80) == HUD_BTN_GROUP_1);
}

static void test_force_attack_tap_latch(void)
{
	MobileTouchHUD hud;
	MobileTouchHud_Init(&hud);
	MobileTouchHudAction action;

	// Tap force attack (< 300ms)
	MobileTouchHud_FingerDown(&hud, 1, 6, 50, 1000, &action);
	assert(action.type == HUD_ACTION_FORCE_ATTACK_CHANGED);
	assert(MobileTouchHud_IsForceAttackActive(&hud));

	MobileTouchHud_FingerUp(&hud, 1, 6, 50, 1100, &action);
	assert(action.type == HUD_ACTION_FORCE_ATTACK_CHANGED);
	assert(hud.force_attack_latched == 1);
	assert(MobileTouchHud_IsForceAttackActive(&hud));

	// Attack fires on map -> latch cleared
	MobileTouchHud_OnAttackFired(&hud, &action);
	assert(action.type == HUD_ACTION_FORCE_ATTACK_CHANGED);
	assert(hud.force_attack_latched == 0);
	assert(!MobileTouchHud_IsForceAttackActive(&hud));
}

static void test_force_attack_hold(void)
{
	MobileTouchHUD hud;
	MobileTouchHud_Init(&hud);
	MobileTouchHudAction action;

	// Hold force attack (> 300ms)
	MobileTouchHud_FingerDown(&hud, 1, 6, 50, 1000, &action);
	assert(hud.force_attack_held == 1);
	assert(MobileTouchHud_IsForceAttackActive(&hud));

	MobileTouchHud_FingerUp(&hud, 1, 6, 50, 1500, &action);
	assert(hud.force_attack_held == 0);
	assert(hud.force_attack_latched == 0);
	assert(!MobileTouchHud_IsForceAttackActive(&hud));
}

static void test_group_single_tap_select(void)
{
	MobileTouchHUD hud;
	MobileTouchHud_Init(&hud);
	MobileTouchHudAction action;

	MobileTouchHud_FingerDown(&hud, 2, 6, 80, 2000, &action);
	assert(hud.active_button == HUD_BTN_GROUP_1);

	MobileTouchHud_FingerUp(&hud, 2, 6, 80, 2100, &action);
	assert(action.type == HUD_ACTION_GROUP_SELECT);
	assert(action.param == 0);
	assert(action.vk == VK_1);
}

static void test_group_double_tap_center(void)
{
	MobileTouchHUD hud;
	MobileTouchHud_Init(&hud);
	MobileTouchHudAction action;

	// First tap at 2000ms
	MobileTouchHud_FingerDown(&hud, 2, 6, 80, 2000, &action);
	MobileTouchHud_FingerUp(&hud, 2, 6, 80, 2080, &action);
	assert(action.type == HUD_ACTION_GROUP_SELECT);

	// Second tap at 2200ms (< 400ms interval)
	MobileTouchHud_FingerDown(&hud, 2, 6, 80, 2200, &action);
	MobileTouchHud_FingerUp(&hud, 2, 6, 80, 2280, &action);
	assert(action.type == HUD_ACTION_GROUP_CENTER);
	assert(action.param == 0);
	assert(action.vk == VK_1);
}

static void test_group_long_press_assign(void)
{
	MobileTouchHUD hud;
	MobileTouchHud_Init(&hud);
	MobileTouchHudAction action;

	// Finger down on Group 2 at 3000ms
	MobileTouchHud_FingerDown(&hud, 3, 6, 110, 3000, &action);
	assert(hud.active_button == HUD_BTN_GROUP_2);

	// Update at 3200ms -> not yet
	MobileTouchHud_Update(&hud, 3200, &action);
	assert(action.type == HUD_ACTION_NONE);
	assert(hud.group_assigned[1] == 0);

	// Update at 3400ms (>= 350ms duration) -> triggers assign!
	MobileTouchHud_Update(&hud, 3400, &action);
	assert(action.type == HUD_ACTION_GROUP_ASSIGN);
	assert(action.param == 1);
	assert(action.vk == VK_1 + 1);
	assert(hud.group_assigned[1] == 1);

	// Subsequent update while held doesn't re-trigger
	MobileTouchHud_Update(&hud, 3450, &action);
	assert(action.type == HUD_ACTION_NONE);

	// Finger up doesn't fire duplicate action
	MobileTouchHud_FingerUp(&hud, 3, 6, 110, 3500, &action);
	assert(action.type == HUD_ACTION_NONE);
}

static void test_stop_and_scatter(void)
{
	MobileTouchHUD hud;
	MobileTouchHud_Init(&hud);
	MobileTouchHudAction action;

	// Stop
	MobileTouchHud_FingerDown(&hud, 1, 6, 195, 4000, &action);
	MobileTouchHud_FingerUp(&hud, 1, 6, 195, 4080, &action);
	assert(action.type == HUD_ACTION_KEY_PULSE);
	assert(action.vk == VK_S);

	// Scatter
	MobileTouchHud_FingerDown(&hud, 1, 6, 220, 4200, &action);
	MobileTouchHud_FingerUp(&hud, 1, 6, 220, 4280, &action);
	assert(action.type == HUD_ACTION_KEY_PULSE);
	assert(action.vk == 0x58);
}

static void test_modifier_override_filtering(void)
{
	assert(MobileKeyMessage_GetModifierOverride(WM_KEYDOWN, MOBILE_KEY_FORCE_CTRL_LPARAM) == MOBILE_KEY_MOD_FORCE_CTRL);
	assert(MobileKeyMessage_GetModifierOverride(WM_KEYDOWN, MOBILE_KEY_FORCE_ALT_LPARAM) == MOBILE_KEY_MOD_FORCE_ALT);
	assert(MobileKeyMessage_GetModifierOverride(WM_KEYDOWN, MOBILE_KEY_UNMODIFIED_LPARAM) == MOBILE_KEY_MOD_UNMODIFIED);
	assert(MobileKeyMessage_GetModifierOverride(WM_KEYDOWN, 0) == MOBILE_KEY_MOD_NONE);

	// Force Ctrl override
	assert(MobileKeyMessage_FilterKeyState(MOBILE_KEY_MOD_FORCE_CTRL, VK_CONTROL, 0) == (short)0x8000);
	assert(MobileKeyMessage_FilterKeyState(MOBILE_KEY_MOD_FORCE_CTRL, VK_MENU, (short)0x8000) == 0);
	assert(MobileKeyMessage_FilterKeyState(MOBILE_KEY_MOD_FORCE_CTRL, VK_SHIFT, (short)0x8000) == 0);

	// Force Alt override
	assert(MobileKeyMessage_FilterKeyState(MOBILE_KEY_MOD_FORCE_ALT, VK_MENU, 0) == (short)0x8000);
	assert(MobileKeyMessage_FilterKeyState(MOBILE_KEY_MOD_FORCE_ALT, VK_CONTROL, (short)0x8000) == 0);
	assert(MobileKeyMessage_FilterKeyState(MOBILE_KEY_MOD_FORCE_ALT, VK_SHIFT, (short)0x8000) == 0);
}

int main(void)
{
	test_initial_state();
	test_collapse_and_expand();
	test_force_attack_tap_latch();
	test_force_attack_hold();
	test_group_single_tap_select();
	test_group_double_tap_center();
	test_group_long_press_assign();
	test_stop_and_scatter();
	test_modifier_override_filtering();
	return 0;
}
