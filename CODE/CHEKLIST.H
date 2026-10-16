/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef CHEKLIST_H
#define CHEKLIST_H

#include "list.h"

class CheckObject
{
	public:
		CheckObject(char const * text = 0, bool checked=false) :
			Text(text),
			IsChecked(checked)
		{};

		char const * Text;
		bool IsChecked;
};


class CheckListClass : public ListClass
{
	public:
		/*
		**	Constructor/Destructor
		*/
		CheckListClass(int id, int x, int y, int w, int h, TextPrintType flags,
			void const * up, void const * down);
		~CheckListClass(void);

		virtual int Add_Item(int text) {return ListClass::Add_Item(text);}
		virtual int Add_Item(char const * text);
		virtual char const * Current_Item(void) const;
		virtual char const * Get_Item(int index) const;
		virtual void Remove_Item(char const * text);
		virtual void Remove_Item(int text) {ListClass::Remove_Item(text);}
		virtual void Set_Selected_Index(char const * text);
		virtual void Set_Selected_Index(int index) {ListClass::Set_Selected_Index(index);};

		/*
		**	Checkmark utility functions
		*/
		void Check_Item(int index, bool checked);	// sets checked state of item
		bool Is_Checked(int index) const;				// gets checked state of item

		void Set_Read_Only(int rdonly) {IsReadOnly = rdonly;}

		/*
		**	This defines the ASCII value of the checkmark character & non-checkmark
		**	character.
		*/
		typedef enum CheckListClassEnum {
			CHECK_CHAR = '\3',
			UNCHECK_CHAR = ' '
		} CheckListClassEnum;

	protected:
		virtual int Action(unsigned flags, KeyNumType &key);
		virtual void Draw_Entry(int index, int x, int y, int width, int selected);

	private:
		bool IsReadOnly;
};


#endif
