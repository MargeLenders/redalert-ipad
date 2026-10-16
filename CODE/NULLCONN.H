/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef NULLCONN_H
#define NULLCONN_H


/*
********************************* Includes **********************************
*/
#include "connect.h"
#include "commlib.h"

/*
********************************** Defines **********************************
*/
#define	PACKET_SERIAL_START				0xDABD
#define	PACKET_SERIAL_VERIFY				0xDEAF

#define	PACKET_SERIAL_OVERHEAD_SIZE	(sizeof( SerialHeaderType ) + sizeof( SerialCRCType ))

typedef struct {
	unsigned short MagicNumber;
	unsigned short Length;
	unsigned short MagicNumber2;
} SerialHeaderType;

typedef struct {
	int SerialCRC;
} SerialCRCType;


/*
***************************** Class Declaration *****************************
*/
class NullModemConnClass : public ConnectionClass
{
	/*
	---------------------------- Public Interface ----------------------------
	*/
	public:
		/*.....................................................................
		Constructor/destructor.
		.....................................................................*/
		NullModemConnClass (int numsend, int numrecieve, int maxlen,
			unsigned short magicnum);
		virtual ~NullModemConnClass ();

		/*.....................................................................
		Initialization.
		.....................................................................*/
#ifdef WIN32
		void Init (HANDLE port_handle);
#else	//WIN32
		void Init (PORT *port);
#endif	//WIN32

		/*.....................................................................
		Utility routines.
		.....................................................................*/
		unsigned long Actual_Max_Packet (void) { return (MaxPacketLen +
			(sizeof(SerialHeaderType)) + sizeof(int) + sizeof (char)); }

		/*.....................................................................
		This routine computes a CRC value for the given buffer.
		.....................................................................*/
		static int Compute_CRC(char *buf, int buflen);

		/*.....................................................................
		This routine returns the number of bytes extra added the packet
		for communication.
		.....................................................................*/
		static int Packet_Overhead_Size( void );

	/*
	--------------------------- Private Interface ----------------------------
	*/
	protected:
		/*.....................................................................
		This routine actually performs a hardware-dependent data send.
		.....................................................................*/
		virtual int Send (char *buf, int buflen, void *extrabuf, int extralen);
#ifdef WIN32
		/*
		** This is the winsoze port handle
		*/
		HANDLE PortHandle;
#else	//WIN32
		/*.....................................................................
		This is the PORT value used by the GreenLeaf calls.
		.....................................................................*/
		PORT *Port;
#endif	//WIN32

		/*.....................................................................
		This buffer is a staging area for data sent out; it includes the
		packet sent by the parent class (which includes the application's
		packet, plus the CommHeaderType header), plus:
		- 2-byte buffer start ID
		- 2-byte length
		- 4-byte CRC value (at the end of the buffer)
		This is the actual packet that gets sent across the serial line.
		.....................................................................*/
		char *SendBuf;
};

#endif

/************************** end of nullconn.h ******************************/

