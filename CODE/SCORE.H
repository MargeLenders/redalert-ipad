/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef SCORE_H
#define SCORE_H

#include	"unit.h"
#include	"building.h"

class ScoreClass {
	public:
		ScoreClass(void) {};
		ScoreClass(NoInitClass const &) {};

		int Score;
		int NKilled;
		int GKilled;
		int CKilled;
		int NBKilled;
		int GBKilled;
		int CBKilled;
		int NHarvested;
		int GHarvested;
		int CHarvested;
		unsigned long ElapsedTime;
		TTimerClass<SystemTimerClass> RealTime;

		void Init(void);
		void Presentation(void);

		/*
		**	File I/O.
		*/
		bool Load(Straw & file);
		bool Save(Pipe & file) const;
		void Code_Pointers(void);
		void Decode_Pointers(void);

	private:
		unsigned char *ChangingGun;

		void ScoreDelay(int ticks);
		void Pulse_Bar_Graph(void);
		void Print_Graph_Title(int,int);
		void Print_Minutes(int minutes);
		void Count_Up_Print(char *str, int percent, int max, int xpos, int ypos);
		void Show_Credits(int house, char const pal[]);
		void Do_GDI_Graph(void const * yellowptr, void const * redptr, int gdikilled, int nodkilled, int ypos);
		void Do_Nod_Casualties_Graph(void);
		void Do_Nod_Buildings_Graph(void);
		void Input_Name(char str[], int xpos, int ypos, char const pal[]);
};

class ScoreAnimClass {
	public:
		ScoreAnimClass(int x, int y, void const * data);
		int XPos;
		int YPos;
		CDTimerClass<SystemTimerClass> Timer;
		void const * DataPtr;
		virtual void Update(void) {} ;
		virtual ~ScoreAnimClass(void) {DataPtr=0;} ;
};

class ScoreCredsClass : public ScoreAnimClass {
	public:
		int Stage;
		int MaxStage;
		int TimerReset;
		void const * CashTurn;
		void const * Clock1;

		virtual void Update(void);
		ScoreCredsClass(int xpos, int ypos, void const * data, int max, int timer);
		virtual ~ScoreCredsClass(void) {CashTurn=0;Clock1=0;};
};

class ScoreTimeClass : public ScoreAnimClass {
	public:
		int Stage;
		int MaxStage;
		int TimerReset;
		virtual void Update(void);
		ScoreTimeClass(int xpos, int ypos, void const * data, int max, int timer);
		virtual ~ScoreTimeClass(void) {};
};

class ScorePrintClass : public ScoreAnimClass {
	public:
		int Background;
		int Stage;
		void const * PrimaryPalette;
		virtual void Update(void);
		ScorePrintClass(void const * string, int xpos, int ypos, void const * palette, int background=TBLACK);
		ScorePrintClass( int  string, int xpos, int ypos, void const * palette, int background=TBLACK);
		virtual ~ScorePrintClass(void) {PrimaryPalette=0;};
};

class ScoreScaleClass : public ScoreAnimClass {
	public:
		int Stage;
		char const * Palette;
		virtual void Update(void);
		ScoreScaleClass(void const * data, int xpos, int ypos, char const pal[]);
		virtual ~ScoreScaleClass(void) {Palette=0;};

};

#define MAXSCOREOBJS		8
extern ScoreAnimClass *ScoreObjs[MAXSCOREOBJS];

void Multi_Score_Presentation(void);

#endif
