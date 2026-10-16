/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#include "function.h"

#ifdef WIN32

#include "ipx95.h"

/*
** Instance handle for the THIPX32 .DLL
*/
HINSTANCE	IpxDllInstance = NULL;

/*
** Function pointers
*/
//extern "C" {
	IPXInitialiseType					IPX_Initialise = NULL;
	IPXGetOutstandingBuffer95Type	IPX_Get_Outstanding_Buffer95 = NULL;
	IPXShutDown95Type             IPX_Shut_Down95 = NULL;
	IPXSendPacket95Type           IPX_Send_Packet95 = NULL;
	IPXBroadcastPacket95Type      IPX_Broadcast_Packet95 = NULL;
	IPXStartListening95Type       IPX_Start_Listening95 = NULL;
	IPXOpenSocket95Type           IPX_Open_Socket95 = NULL;
	IPXCloseSocket95Type          IPX_Close_Socket95 = NULL;
	IPXGetConnectionNumber95Type  IPX_Get_Connection_Number95 = NULL;
	IPXGetLocalTarget95           IPX_Get_Local_Target95 = NULL;
//}

char const *FunctionNames[] = {
	"_IPX_Initialise",
	"_IPX_Get_Outstanding_Buffer95",
	"_IPX_Shut_Down95",
	"_IPX_Send_Packet95",
	"_IPX_Broadcast_Packet95",
	"_IPX_Start_Listening95",
	"_IPX_Open_Socket95",
	"_IPX_Close_Socket95",
	"_IPX_Get_Connection_Number95",
	"_IPX_Get_Local_Target95",
	NULL
};

extern void Get_OS_Version (void);
bool				WindowsNT = false;


/***********************************************************************************************
 * Load_IPX_Dll -- Loads the THIPX32 DLL                                                       *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   true if DLL loaded                                                                *
 *                                                                                             *
 * WARNINGS: This call will fail under NT due to a side effect of loading the THIPX32.DLL      *
 *           which causes the 16 bit DLL THIPX16.DLL to load.                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    4/1/97 11:40AM ST : Created                                                              *
 *=============================================================================================*/
bool Load_IPX_Dll (void)
{
	Get_OS_Version();
	if (WindowsNT) return (false);

	SetErrorMode( SEM_NOOPENFILEERRORBOX );
	IpxDllInstance = LoadLibrary ( "THIPX32.DLL" );
	SetErrorMode ( 0 );

	if ( IpxDllInstance ){

		const char		*function_name;
		unsigned long 	*fptr = (unsigned long *) &IPX_Initialise;
		int				count = 0;

		do {
			function_name = FunctionNames[count];
			if (function_name){
				*fptr = (unsigned long) GetProcAddress (IpxDllInstance, function_name);
				assert (*fptr != NULL);
				fptr++;
				count++;
			}

		} while ( function_name );

		return (true);

	}else{
		return (false);
	}
}



/***********************************************************************************************
 * Unload_IPX_Dll -- Frees the THIPX32 library                                                 *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   Nothing                                                                           *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    4/1/97 2:37PM ST : Created                                                               *
 *=============================================================================================*/
void Unload_IPX_Dll (void)
{
	if (IpxDllInstance){
		FreeLibrary (IpxDllInstance);
		IpxDllInstance = NULL;
	}
}


int IPX_Open_Socket(unsigned short socket)
{
	return ( IPX_Open_Socket95((int)socket));
}

int IPX_Close_Socket(unsigned short socket)
{
	IPX_Close_Socket95((int)socket);
	return (0);
}


int IPX_Get_Connection_Number(void)
{
	return (IPX_Get_Connection_Number95());
}



int IPX_Broadcast_Packet(unsigned char * buf, int buflen)
{
	return(IPX_Broadcast_Packet95(buf, buflen));
}

extern "C"{
	extern void __cdecl Int3(void);
}

int IPX_Get_Local_Target(unsigned char * dest_network, unsigned char * dest_node,
	unsigned short dest_socket, unsigned char * bridge_address)
{
	//Int3();
	return (IPX_Get_Local_Target95(dest_network, dest_node, dest_socket, bridge_address));
}


#endif	//WIN32
