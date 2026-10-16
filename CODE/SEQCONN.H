/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef SEQCONN_H
#define SEQCONN_H

#include "connect.h"
#include "comqueue.h"


/*
***************************** Class Declaration *****************************
*/
class SequencedConnClass : public ConnectionClass
{
	/*
	---------------------------- Public Interface ----------------------------
	*/
	public:
		/*.....................................................................
		Constructor/destructor.
		.....................................................................*/
		SequencedConnClass (int numsend, int numrecieve, int maxlen, 
			unsigned short magicnum, unsigned long retry_delta,
			unsigned long max_retries, unsigned long timeout);
		virtual ~SequencedConnClass ();

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
		The packet queue.
		.....................................................................*/
		CommQueueClass *Queue;

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

};

#endif
/*************************** end of seqconn.h ******************************/
