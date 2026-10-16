/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef MSGLIST_H
#define MSGLIST_H

//***************************************************************************
// Defines
//***************************************************************************
//---------------------------------------------------------------------------
//	Max length of inter-player message buffers.  Messages.Init() should specify
// a value <= this.  For editing messages, the "to" field length is added to
// this length to generate the entire editable message length.  For displayed
// messages, a "From" prefix length should be added to this value to generate
// the entire max displayable message length.
//---------------------------------------------------------------------------
#define	MAX_MESSAGE_LENGTH		120

//---------------------------------------------------------------------------
// Max # of allowed messages at one time
//---------------------------------------------------------------------------
#define	MAX_NUM_MESSAGES			14

//***************************************************************************
// Forward declarations
//***************************************************************************
class TextLabelClass;

//***************************************************************************
// Class declaration
//***************************************************************************
class MessageListClass {
	public:
		//.....................................................................
		// Constructor/Destructor
		//.....................................................................
		MessageListClass (void);
		~MessageListClass ();

		//.....................................................................
		// Initialization
		//.....................................................................
		void Reset(void);
		void Init (int x, int y, int max_msg, int maxchars, int height,
			int edit_x, int edit_y, int overflow_on, int over_start,
			int over_end, int width = 640);
		TextLabelClass * Add_Message (char const * name, int id, char const * txt,
			PlayerColorType color, TextPrintType style, int timeout);
		int Concat_Message (char const * name, int id, char const * txt, int timeout);

		//.....................................................................
		// Message access utility routines
		//.....................................................................
		char * Get_Message (int id);
		TextLabelClass * Get_Label (int id);

		//.....................................................................
		// Message-editing support routines
		//.....................................................................
		TextLabelClass * Add_Edit(PlayerColorType color, TextPrintType style,
			char *to, char cursor = 0, int width = 640);
		void Remove_Edit (void);
		char * Get_Edit_Buf (void);
		char * Get_Overflow_Buf (void) {return (OverflowBuf);}
		void Clear_Overflow_Buf (void) {OverflowBuf[0] = 0;}
		int Is_Edit(void) {return (IsEdit);}
		void Set_Edit_Color(PlayerColorType color);

		//.....................................................................
		// Maintenance routines
		//.....................................................................
		int Manage (void);
		int Input (KeyNumType &input);
		void Draw(void);
		int Num_Messages(void);
		void Set_Width(int width);
		void Set_Edit_Focus(void);
		bool Has_Edit_Focus(void);

	private:

		//.....................................................................
		// Message parsing
		//.....................................................................
		int Trim_Message(char *dest, char *src, int min_chars, int max_chars,
			int scandir);

		//.....................................................................
		// Compute the y-coord of the message list
		//.....................................................................
		void Compute_Y(void);

		//.....................................................................
		// Private Data
		//.....................................................................
		TextLabelClass * MessageList;				// list of messages
		int MessageX;									// x-coord of upper-left
		int MessageY;									// y-coord of upper-left
		int MaxMessages;								// max messages allowed
		int MaxChars;									// max allowed chars per message
		int Height;										// height in pixels

		//.....................................................................
		// Data for the edit field: the edit field will either appear at
		// exact coordinates specified by the application, or it will appear
		// vertically above the other messages.
		//.....................................................................
		unsigned EnableOverflow	: 1;					// 1 = enable overflow feature
		unsigned IsEdit				: 1;					// 1 = there's an edit field
		unsigned AdjustEdit			: 1;					// 1 = edit field appears over msgs
		int EditX;										// x-coord of edit field
		int EditY;										// y-coord of edit field
		TextLabelClass *EditLabel;					// ptr to current edit label
		char EditBuf[MAX_MESSAGE_LENGTH + 30];	// buffer for editable message
		char OverflowBuf[MAX_MESSAGE_LENGTH + 30];	// overflow area
		int EditCurPos;								// current edit position
		int EditInitPos;								// initial edit position
		char CursorChar;								// character to use a cursor
		int OverflowStart;							// 1st index for overflow trimming
		int OverflowEnd;								// last index for overflow trimming
		int Width;										// Maximum width in pixels of editable string

		//.....................................................................
		// Buffers provided for messages.  They must be long enough for
		// both the message, and for the "To" prefix on edited messages, or
		// the "Name:" prefix on received messages.
		//.....................................................................
		char MessageBuffers[MAX_NUM_MESSAGES][MAX_MESSAGE_LENGTH + 30];
		char BufferAvail[MAX_NUM_MESSAGES];
};

#endif
/**************************** end of msglist.h *****************************/

