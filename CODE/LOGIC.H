/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef LOGIC_H
#define LOGIC_H

#include	"layer.h"

/***********************************************************************************************
**	Game logic processing is controlled by this class. The graphic and AI logic is handled
**	separately so that on slower machines, the graphic display is least affected.
*/
class LogicClass : public LayerClass
{
	public:
		void AI(void);
		void Detach(TARGET target, bool all=true);
		#ifdef CHEAT_KEYS
		void Debug_Dump(MonoClass *mono) const;
		#endif
};
#endif
