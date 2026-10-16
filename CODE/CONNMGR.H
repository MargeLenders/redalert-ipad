/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef CONNMGR_H
#define CONNMGR_H


/*
***************************** Class Declaration *****************************
*/
class ConnManClass
{
	/*
	---------------------------- Public Interface ----------------------------
	*/
	public:
		/*.....................................................................
		Various useful enums:
		.....................................................................*/
		enum IPXConnTag {
			CONNECTION_NONE = -1			// value of an invalid connection ID
		};

		/*.....................................................................
		Constructor/Destructor.  These currently do nothing.
		.....................................................................*/
		ConnManClass (void) {};
		virtual ~ConnManClass () {};

		/*.....................................................................
		The Service routine:
		- Parses incoming packets, and adds them to the Receive Queue for the
		  Connection Class(s) for this protocol
		- Invokes each connection's Service routine; returns an error if the
		  connection's Service routine indicates an error.
		.....................................................................*/
		virtual int Service (void) = 0;

		/*.....................................................................
		Sending & receiving data
		.....................................................................*/
		virtual int Send_Private_Message (void *buf, int buflen,
			int ack_req = 1, int conn_id = CONNECTION_NONE) = 0;
		virtual int Get_Private_Message (void *buf, int *buflen,
			int *conn_id) = 0;

		/*.....................................................................
		Connection management
		.....................................................................*/
		virtual int Num_Connections(void) = 0;
		virtual int Connection_ID(int index) = 0;
		virtual int Connection_Index(int id) = 0;

		/*.....................................................................
		Queue utility routines
		.....................................................................*/
		virtual int Global_Num_Send(void) = 0;
		virtual int Global_Num_Receive(void) = 0;
		virtual int Private_Num_Send(int id = CONNECTION_NONE) = 0;
		virtual int Private_Num_Receive(int id = CONNECTION_NONE) = 0;

		/*.....................................................................
		Timing management
		.....................................................................*/
		virtual void Reset_Response_Time(void) = 0;
		virtual unsigned long Response_Time(void) = 0;
		virtual void Set_Timing (unsigned long retrydelta,
			unsigned long maxretries, unsigned long timeout) = 0;

		/*.....................................................................
		Debugging
		.....................................................................*/
		virtual void Configure_Debug(int index, int type_offset, int type_size,
			char **names, int namestart, int namecount) = 0;
#ifdef CHEAT_KEYS
		virtual void Mono_Debug_Print(int index, int refresh) = 0;
#endif

	/*
	--------------------------- Private Interface ----------------------------
	*/
	private:
		/*.....................................................................
		This abstract class contains no data members; but a derived class
		will contain:
		- An instance of one or more derived Connection Classes
		- A buffer to store incoming packets
		.....................................................................*/
};

#endif
