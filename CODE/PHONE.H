/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef PHONE_H
#define PHONE_H

#ifndef SESSION_H
#include "session.h"
#endif

class PhoneEntryClass
{
	public:
		enum {
			PHONE_MAX_NAME = 21,
			PHONE_MAX_NUM = 15
		};

		PhoneEntryClass(void)
		{
			Name[0] = 0;
			Number[0] = 0;
			Settings.Port = 0;
			Settings.IRQ = -1;
			Settings.Baud = -1;
			Settings.DialMethod = DIAL_TOUCH_TONE;
			Settings.InitStringIndex = 0;
			Settings.CallWaitStringIndex = CALL_WAIT_CUSTOM;
			Settings.CallWaitString[0] = 0;
			Settings.Compression = false;
			Settings.ErrorCorrection = false;
			Settings.HardwareFlowControl = true;
			Settings.ModemName[0] = 0;
		}

		char Name[PHONE_MAX_NAME];
		char Number[PHONE_MAX_NUM];
		SerialSettingsType Settings;
};

#endif
