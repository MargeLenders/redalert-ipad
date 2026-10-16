/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef LED_H
#define LED_H

class LEDClass
{
	public:
		typedef enum ControlType {
			LED_NOCHANGE,			// Do nothing (just query).
			LED_OFF,					// Turn LED off.
			LED_ON,					// Turn LED on.
			LED_TOGGLE				// Toggle LED state.
		} ControlType;

	protected:
		static int Shift_Control(ControlType control, char bit);

	public:
		static int Scroll_Lock(ControlType control=LED_TOGGLE) {return Shift_Control(control, 0x01);};
		static int Caps_Lock(ControlType control=LED_TOGGLE) {return Shift_Control(control, 0x02);};
		static int Num_Lock(ControlType control=LED_TOGGLE) {return Shift_Control(control, 0x04);};

	private:
		static void Send_To_Keyboard(unsigned char val);
};

#endif
