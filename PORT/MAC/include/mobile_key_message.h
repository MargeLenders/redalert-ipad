#ifndef MOBILE_KEY_MESSAGE_H
#define MOBILE_KEY_MESSAGE_H

#include "windows.h"

#define MOBILE_KEY_UNMODIFIED_LPARAM ((LPARAM)0x52414D50L)
#define MOBILE_KEY_FORCE_CTRL_LPARAM ((LPARAM)0x52414354L)
#define MOBILE_KEY_FORCE_ALT_LPARAM  ((LPARAM)0x5241414CL)

enum MobileKeyModifierOverride {
	MOBILE_KEY_MOD_NONE = 0,
	MOBILE_KEY_MOD_UNMODIFIED = 1,
	MOBILE_KEY_MOD_FORCE_CTRL = 2,
	MOBILE_KEY_MOD_FORCE_ALT = 3
};

static inline int MobileKeyMessage_IsUnmodified(UINT message, LPARAM lparam)
{
	return (message == WM_KEYDOWN || message == WM_KEYUP ||
			message == WM_SYSKEYDOWN || message == WM_SYSKEYUP) &&
		lparam == MOBILE_KEY_UNMODIFIED_LPARAM;
}

static inline int MobileKeyMessage_GetModifierOverride(UINT message, LPARAM lparam)
{
	if (message != WM_KEYDOWN && message != WM_KEYUP &&
			message != WM_SYSKEYDOWN && message != WM_SYSKEYUP) {
		return MOBILE_KEY_MOD_NONE;
	}
	if (lparam == MOBILE_KEY_UNMODIFIED_LPARAM) {
		return MOBILE_KEY_MOD_UNMODIFIED;
	}
	if (lparam == MOBILE_KEY_FORCE_CTRL_LPARAM) {
		return MOBILE_KEY_MOD_FORCE_CTRL;
	}
	if (lparam == MOBILE_KEY_FORCE_ALT_LPARAM) {
		return MOBILE_KEY_MOD_FORCE_ALT;
	}
	return MOBILE_KEY_MOD_NONE;
}

static inline int MobileKeyMessage_IsModifier(int key)
{
	key &= 0xFF;
	return key == VK_SHIFT || key == VK_CONTROL || key == VK_MENU ||
		key == VK_CAPITAL || key == VK_NUMLOCK;
}

static inline short MobileKeyMessage_FilterKeyState(int override_mode, int key, short state)
{
	key &= 0xFF;
	if (override_mode == MOBILE_KEY_MOD_UNMODIFIED) {
		if (MobileKeyMessage_IsModifier(key)) {
			return 0;
		}
	} else if (override_mode == MOBILE_KEY_MOD_FORCE_CTRL) {
		if (key == VK_CONTROL) {
			return (short)0x8000;
		}
		if (key == VK_MENU || key == VK_SHIFT) {
			return 0;
		}
	} else if (override_mode == MOBILE_KEY_MOD_FORCE_ALT) {
		if (key == VK_MENU) {
			return (short)0x8000;
		}
		if (key == VK_CONTROL || key == VK_SHIFT) {
			return 0;
		}
	}
	return state;
}

#endif
