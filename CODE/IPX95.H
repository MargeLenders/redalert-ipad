/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

/*
** Types for function pointers
*/
typedef BOOL __stdcall (*IPXInitialiseType) (void);
typedef BOOL __stdcall (*IPXGetOutstandingBuffer95Type) (unsigned char*);
typedef void __stdcall (*IPXShutDown95Type) (void);
typedef int  __stdcall (*IPXSendPacket95Type) (unsigned char *, unsigned char *, int, unsigned char*, unsigned char*);
typedef int  __stdcall (*IPXBroadcastPacket95Type) (unsigned char *, int);
typedef BOOL __stdcall (*IPXStartListening95Type) (void);
typedef int  __stdcall (*IPXOpenSocket95Type) (int);
typedef void __stdcall (*IPXCloseSocket95Type) (int);
typedef int  __stdcall (*IPXGetConnectionNumber95Type) (void);
typedef int  __stdcall (*IPXGetLocalTarget95) (unsigned char *, unsigned char*, unsigned short, unsigned char*);



/*
** Function pointers
*/
//extern "C"{
	extern IPXInitialiseType					IPX_Initialise;
	extern IPXGetOutstandingBuffer95Type  	IPX_Get_Outstanding_Buffer95;
	extern IPXShutDown95Type              	IPX_Shut_Down95;
	extern IPXSendPacket95Type            	IPX_Send_Packet95;
	extern IPXBroadcastPacket95Type       	IPX_Broadcast_Packet95;
	extern IPXStartListening95Type        	IPX_Start_Listening95;
	extern IPXOpenSocket95Type            	IPX_Open_Socket95;
	extern IPXCloseSocket95Type           	IPX_Close_Socket95;
	extern IPXGetConnectionNumber95Type   	IPX_Get_Connection_Number95;
	extern IPXGetLocalTarget95            	IPX_Get_Local_Target95;
//}

/*
** Functions
*/
bool Load_IPX_Dll (void);
void Unload_IPX_Dll (void);


#if (0)
extern "C"{
	extern BOOL __stdcall IPX_Initialise(void);
	extern BOOL __stdcall IPX_Get_Outstanding_Buffer95(unsigned char *buffer);
	extern void __stdcall IPX_Shut_Down95(void);
	extern int  __stdcall IPX_Send_Packet95(unsigned char *, unsigned char *, int, unsigned char*, unsigned char*);
	extern int  __stdcall IPX_Broadcast_Packet95(unsigned char *, int);
	extern BOOL __stdcall IPX_Start_Listening95(void);
	extern int  __stdcall IPX_Open_Socket95(int socket);
	extern void __stdcall IPX_Close_Socket95(int socket);
	extern int  __stdcall IPX_Get_Connection_Number95(void);
	extern int  __stdcall IPX_Get_Local_Target95(unsigned char *, unsigned char*, unsigned short, unsigned char*);
}
#endif	//(0)

extern bool WindowsNT;
