/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef AUDIO_H
#define AUDIO_H

#include	"memory.h"

class AudioClass {
		char const * Name;	// Name of audio asset.
		void const * Data;	// Loaded audio data.
		int Handle;				// Handle of asset (as it is playing).
		MemoryClass *Mem;		// Pointer to memory handler class.
		unsigned IsMIDI:1;	// Is this a midi file?

	public:
		AudioClass(void);
		AudioClass(char const *name, MemoryClass &mem);
		virtual ~AudioClass(void);

		bool Load(char const *name = 0);
		bool Free(void);
		bool Play(int volume = 0xFF);
		bool Stop(void);
		bool Pause(void);
		bool Resume(void);
		bool Set_Name(char const *name);
		bool Is_Playing(void) const;
		bool Is_Loaded(void) const;
		bool Is_MIDI(void) const;
};

inline AudioClass::AudioClass(void)
{
	Name = 0; 
	Data = 0; 
	Mem = 0;
	Handle = -1;
};

inline AudioClass::AudioClass(char const *name, MemoryClass &mem) 
{
	if (mem) {
		Mem = &mem;
	} else {
		Mem = &::Mem;		// Uses global default memory handler.
	}
	Name = strdup(name);
	Data = 0;
	Handle = -1;
};

inline AudioClass::~AudioClass(void)
{
	if (GameActive) {
		if (Name) free(Name);
		if (Data) Mem->Free(Data);
		Name = 0;
		Data = 0;
		Handle = -1;
	}
};


#endif
