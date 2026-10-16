/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef THEME_H
#define THEME_H

class ThemeClass
{
	private:
		static char const * Theme_File_Name(ThemeType theme);

		int Current;			// Handle to current score.
		ThemeType Score;		// Score number currently being played.
		ThemeType Pending;	// Score to play next.

		typedef struct {
			char const * Name;	// Filename of score.
			int Fullname;			// Text number for full score name.
			int Scenario;			// Scenario when it first becomes available.
			int Duration;			// Duration of theme in seconds.
			bool Normal;			// Allowed in normal game play?
			bool Repeat;			// Always repeat this score?
			bool Available;		// Is the score available?
			int Owner;				// What houses are allowed to play this theme (bit field)?
		} ThemeControl;

		static ThemeControl _themes[THEME_COUNT];

		enum {
			THEME_DELAY=TIMER_SECOND
		};

	public:
		ThemeClass(void);

		ThemeType From_Name(char const * name) const;
		ThemeType Next_Song(ThemeType index) const;
		ThemeType What_Is_Playing(void) const {return Score;}
		bool Is_Allowed(ThemeType index) const;
		bool Is_Regular(ThemeType theme) const {return(theme != THEME_NONE && _themes[theme].Normal);}
		char const * Base_Name(ThemeType index) const;
		char const * Full_Name(ThemeType index) const;
		int Max_Themes(void) const {return THEME_COUNT;}
		int Play_Song(ThemeType index);
		int Still_Playing(void) const;
		int Track_Length(ThemeType index) const;
		static void Scan(void);
		void AI(void);
		void Fade_Out(void) {Queue_Song(THEME_QUIET);}
		void Queue_Song(ThemeType index);
		void Set_Theme_Data(ThemeType theme, int scenario, int owners);
		void Stop(void);
		void Suspend(void);
};

#endif
