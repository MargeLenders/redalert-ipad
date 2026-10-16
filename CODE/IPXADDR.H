/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef IPXADDR_H
#define IPXADDR_H

#include "ipx.h"				// for NetNumType & NetNodeType


/*
***************************** Class Declaration *****************************
*/
class IPXAddressClass
{
	/*
	---------------------------- Public Interface ----------------------------
	*/
	public:
		/*.....................................................................
		Constructors:
		.....................................................................*/
		IPXAddressClass(void);
		IPXAddressClass(NetNumType net, NetNodeType node);
		IPXAddressClass(IPXHeaderType *header);

		/*.....................................................................
		Set the address from explicit variables, or from the SOURCE values
		in an IPX packet header.
		.....................................................................*/
		void Set_Address(NetNumType net, NetNodeType node);
		void Set_Address(IPXHeaderType *header);
		/*.....................................................................
		Get the address values explicitly, or copy them into the DESTINATION
		values in an IPX packet header.
		.....................................................................*/
		void Get_Address (NetNumType net, NetNodeType node);
		void Get_Address(IPXHeaderType *header);

		/*.....................................................................
		Tells if this address is a broadcast address
		.....................................................................*/
		int Is_Broadcast(void);

		/*.....................................................................
		Overloaded operators:
		.....................................................................*/
		int operator == (IPXAddressClass & addr);
		int operator != (IPXAddressClass & addr);
		int operator > (IPXAddressClass &addr);
		int operator < (IPXAddressClass &addr);
		int operator >= (IPXAddressClass &addr);
		int operator <= (IPXAddressClass &addr);
	/*
	-------------------------- Protected Interface ---------------------------
	*/
	protected:
	/*
	--------------------------- Private Interface ----------------------------
	*/
	private:
		NetNumType NetworkNumber;
		NetNodeType NodeAddress;
};

#endif

/**************************** end of ipxaddr.h *****************************/
