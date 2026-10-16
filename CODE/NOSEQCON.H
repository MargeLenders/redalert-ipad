/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef NONSEQCONN_H
#define NONSEQCONN_H


/*
********************************* Includes **********************************
*/
#include "connect.h"
#include "combuf.h"


/*
***************************** Class Declaration *****************************
*/
class NonSequencedConnClass : public ConnectionClass
{
	/*
	---------------------------- Public Interface ----------------------------
	*/
	public:
		/*.....................................................................
		Constructor/destructor.
		.....................................................................*/
		NonSequencedConnClass (int numsend, int numrecieve, int maxlen, 
			unsigned short magicnum, unsigned long retry_delta,
			unsigned long max_retries, unsigned long timeout);
		virtual ~NonSequencedConnClass ();

		/*.....................................................................
		Initialization.
		.....................................................................*/
		virtual void Init (void);

		/*.....................................................................
		Send/Receive routines.
		.....................................................................*/
		virtual int Send_Packet (void * buf, int buflen, int ack_req);
		virtual int Receive_Packet (void * buf, int buflen);
		virtual int Get_Packet (void * buf, int *buflen);

		/*.....................................................................
		The packet "queue"; this non-sequenced version isn't really much of
		a queue, but more of a repository.
		.....................................................................*/
		CommBufferClass *Queue;

	/*
	-------------------------- Protected Interface ---------------------------
	*/
	protected:
		/*.....................................................................
		Routines to service the Send & Receive queues.
		.....................................................................*/
		virtual int Service_Send_Queue (void);
		virtual int Service_Receive_Queue (void);

		/*.....................................................................
		Running totals of # of packets we send & receive which require an ACK, 
		and those that don't.
		.....................................................................*/
		unsigned long NumRecNoAck;
		unsigned long NumRecAck;
		unsigned long NumSendNoAck;
		unsigned long NumSendAck;

		/*.....................................................................
		This is the ID of the last consecutively-received packet; anything older 
		than this, we know is a resend.  Anything newer than this MUST be lying 
		around in the Queue for us to detect it as a resend.
		.....................................................................*/
		unsigned long LastSeqID;

		/*.....................................................................
		This is the ID of the PACKET_DATA_ACK packet we read last; it ensures
		that the application reads that type of packet in order.
		.....................................................................*/
		unsigned long LastReadID;
};

#endif


