/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef COMQUEUE_H
#define COMQUEUE_H



/*---------------------------------------------------------------------------
This is one output queue entry
---------------------------------------------------------------------------*/
typedef struct {
	unsigned int IsActive	: 1;	// 1 = this entry is ready to be processed
	unsigned int IsACK		: 1;	// 1 = ACK received for this packet
	unsigned long FirstTime;		// time this packet was first sent
	unsigned long LastTime;			// time this packet was last sent
	unsigned long SendCount;		// # of times this packet has been sent
	int BufLen;							// size of the packet stored in this entry
	char *Buffer;						// the data packet
} SendQueueType;

/*---------------------------------------------------------------------------
This is one input queue entry
---------------------------------------------------------------------------*/
typedef struct {
	unsigned int IsActive	: 1;	// 1 = this entry is ready to be processed
	unsigned int IsRead		: 1;	// 1 = caller has read this entry
	unsigned int IsACK		: 1;	// 1 = ACK sent for this packet
	int BufLen;							// size of the packet stored in this entry
	char *Buffer;						// the data packet
} ReceiveQueueType;

/*
***************************** Class Declaration *****************************
*/
class CommQueueClass
{
	/*
	---------------------------- Public Interface ----------------------------
	*/
	public:
		/*
		....................... Constructor/Destructor ........................
		*/
		CommQueueClass(int numsend, int numrecieve, int maxlen);
		virtual ~CommQueueClass();
		void Init(void);

		/*
		......................... Send Queue routines .........................
		*/
		int Queue_Send(void *buf, int buflen);			// add to Send queue
		int UnQueue_Send(void *buf, int *buflen);		// remove from Send queue
		SendQueueType * Next_Send(void);					// ptr to next avail entry
		int Num_Send(void) {return (SendCount);}		// # entries in queue
		int Max_Send(void) { return (MaxSend);}		// max # send queue entries
		SendQueueType * Get_Send(int index);			// random access to queue
		unsigned long Send_Total(void) {return (SendTotal);}

		/*
		....................... Receive Queue routines ........................
		*/
		int Queue_Receive(void *buf, int buflen);		// add to Receive queue
		int UnQueue_Receive(void *buf, int *buflen);	// remove from Receive queue
		ReceiveQueueType * Next_Receive(void);			// ptr to next avail entry
		int Num_Receive(void) {return (ReceiveCount);}	// # entries in queue
		int Max_Receive(void) { return (MaxReceive); }	// max # recv queue entries
		ReceiveQueueType * Get_Receive(int index);	// random access to queue
		unsigned long Receive_Total(void) {return (ReceiveTotal);}

		/*
		....................... Response time routines ........................
		*/
		void Add_Delay(unsigned long delay);	// accumulates response time
		unsigned long Avg_Response_Time(void);	// gets mean response time
		unsigned long Max_Response_Time(void);	// gets max response time
		void Reset_Response_Time(void);			// resets computations

		/*
		........................ Debug output routines ........................
		*/
		void Configure_Debug(int offset, int size, char **names, int maxnames);
		void Mono_Debug_Print(int refresh = 0);
		void Mono_Debug_Print2(int refresh = 0);

	/*
	--------------------------- Private Interface ----------------------------
	*/
	private:
		/*
		.......................... Limiting variables .........................
		*/
		int MaxSend;							// max # send queue entries
		int MaxReceive;						// max # receive queue entries
		int MaxPacketSize;					// max size of a packet, in bytes

		/*
		....................... Response time variables .......................
		*/
		unsigned long DelaySum;				// sum of last 4 delay times
		unsigned long NumDelay;				// current # delay times summed
		unsigned long MeanDelay;			// current average delay time
		unsigned long MaxDelay;				// max delay ever for this queue

		/*
		........................ Send Queue variables .........................
		*/
		SendQueueType * SendQueue;			// incoming packets
		int SendCount; 						// # packets in the queue
		int SendNext;							// next entry read from queue
		int SendEmpty;							// next empty spot in queue
		unsigned long SendTotal;			// total # added to send queue

		/*
		....................... Receive Queue variables .......................
		*/
		ReceiveQueueType * ReceiveQueue;		// outgoing packets
		int ReceiveCount;							// # packets in the queue
		int ReceiveNext;							// next entry read from queue
		int ReceiveEmpty;							// next empty spot in queue
		unsigned long ReceiveTotal;			// total # added to receive queue

		/*
		......................... Debugging Variables .........................
		*/
		int DebugOffset;							// offset into app's packet for ID
		int DebugSize;								// size of app's ID
		char **DebugNames;						// ptr to array of app-specific names
		int DebugMaxNames;						// max # of names in array
};

#endif

/*************************** end of comqueue.h *****************************/

