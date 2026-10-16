/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef EDIT_H
#define EDIT_H

class EditClass : public ControlClass
{
	public:
		typedef enum EditStyle {
			ALPHA			=0x0001,		// Edit accepts alphabetic characters.
			NUMERIC		=0x0002,		// Edit accepts numbers.
			MISC			=0x0004,		// Edit accepts misc graphic characters.
			UPPERCASE	=0x0008,		// Force to upper case.
			ALPHANUMERIC=(int)ALPHA|(int)NUMERIC|(int)MISC
		} EditStyle;

		EditClass (int id, char * text, int max_len, TextPrintType flags, int x, int y, int w=-1, int h=-1, EditStyle style=ALPHANUMERIC);
		virtual ~EditClass(void);

		virtual void Set_Focus(void);
		virtual void Clear_Focus(void);
		virtual int  Draw_Me(int forced);
		virtual void Set_Text(char * text, int max_len);
		virtual char * Get_Text(void) {return(String);};
		void Set_Color (RemapControlType * color) { Color = color; }

		void Set_Read_Only(int rdonly) {IsReadOnly = rdonly;}

	protected:

		/*
		**	These are the text size and style flags to be used when displaying the text
		**	of the edit gadget.
		*/
		TextPrintType TextFlags;

		/*
		**	Input flags that control what characters are allowed in the string.
		*/
		EditStyle EditFlags;

		/*
		**	Pointer to text staging buffer and the maximum length of the string it
		**	can contain.
		*/
		char *String;
		int MaxLength;

		/*
		**	This is the current length of the string. This length will never exceed the
		**	MaxLength allowed.
		*/
		int Length;

		/*
		**	This is the desired color of the edit control.
		*/
		RemapControlType * Color;

		virtual int Action (unsigned flags, KeyNumType &key);
		virtual void Draw_Background(void);
		virtual void Draw_Text(char const * text);
		virtual bool Handle_Key(KeyASCIIType ascii);

	private:
		int IsReadOnly;
};

inline EditClass::EditStyle operator |(EditClass::EditStyle left, EditClass::EditStyle right) { return (EditClass::EditStyle)((int)left | (int)right); }
inline EditClass::EditStyle operator &(EditClass::EditStyle left, EditClass::EditStyle right) { return (EditClass::EditStyle)((int)left & (int)right); }
inline EditClass::EditStyle operator ~(EditClass::EditStyle value) { return (EditClass::EditStyle)(~(int)value); }

#endif
