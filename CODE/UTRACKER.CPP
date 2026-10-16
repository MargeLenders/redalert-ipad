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

/*
** Define host to network to host functions for DOS
*/
#ifndef WIN32

#define htonl(val) 0
#define ntohl(val) 0

#endif	//WIN32


/***********************************************************************************************
 * UTC::UnitTrackerClass -- Class constructor                                                  *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Number of unit types to reserve space for                                         *
 *                                                                                             *
 * OUTPUT:   Nothing                                                                           *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    6/7/96 0:10AM ST : Created                                                               *
 *=============================================================================================*/
UnitTrackerClass::UnitTrackerClass (int unit_count)
{
	UnitTotals = new long [unit_count];		// Allocate memory for the unit totals
	UnitCount = unit_count;						// Keep a record of how many unit entries there are
	InNetworkFormat = 0;							// The unit entries are in host format
	Clear_Unit_Total();							// Clear each entry
}


/***********************************************************************************************
 * UTC::~UnitTrackerClass -- Class destructor                                                  *
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
 *    6/7/96 0:10AM ST : Created                                                               *
 *=============================================================================================*/
UnitTrackerClass::~UnitTrackerClass (void)
{
	delete UnitTotals;
}



/***********************************************************************************************
 * UTC::Increment_Unit_Total -- Increment the total for the specefied unit                     *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Unit number                                                                       *
 *                                                                                             *
 * OUTPUT:   Nothing                                                                           *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    6/7/96 0:12AM ST : Created                                                               *
 *=============================================================================================*/
void UnitTrackerClass::Increment_Unit_Total(int unit_type)
{
	UnitTotals[unit_type]++;
}


/***********************************************************************************************
 * UTC::Decrement_Unit_Total -- Decrement the total for the specefied unit                     *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Unit number                                                                       *
 *                                                                                             *
 * OUTPUT:   Nothing                                                                           *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    6/7/96 0:13AM ST : Created                                                               *
 *=============================================================================================*/
void UnitTrackerClass::Decrement_Unit_Total(int unit_type)
{
	UnitTotals[unit_type]--;
}


/***********************************************************************************************
 * UTC::Get_All_Totals -- Returns a pointer to the start of the unit totals list               *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   Ptr to unit totals list                                                           *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    6/7/96 0:13AM ST : Created                                                               *
 *=============================================================================================*/
long *UnitTrackerClass::Get_All_Totals (void)
{
	return (UnitTotals);
}


/***********************************************************************************************
 * UTC::Clear_Unit_Total -- Clear out all the unit totals                                      *
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
 *    6/7/96 0:14AM ST : Created                                                               *
 *=============================================================================================*/
void UnitTrackerClass::Clear_Unit_Total (void)
{
	memset (UnitTotals, 0, UnitCount * sizeof(long) );
}



/***********************************************************************************************
 * UTC::To_Network_Format -- Changes all unit totals to network format for the internet        *
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
 *    6/7/96 0:15AM ST : Created                                                               *
 *=============================================================================================*/
void UnitTrackerClass::To_Network_Format (void)
{
	if (!InNetworkFormat){
		for (int i=0 ; i<UnitCount ; i++){
			UnitTotals[i] = htonl (UnitTotals[i]);
		}
	}
	InNetworkFormat = 1;		// Flag that data is now in network format
}


/***********************************************************************************************
 * UTC::To_PC_Format -- Changes all unit totals to PC format from network format               *
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
 *    6/7/96 0:15AM ST : Created                                                               *
 *=============================================================================================*/
void UnitTrackerClass::To_PC_Format (void)
{
	if (InNetworkFormat){
		for (int i=0 ; i<UnitCount ; i++){
			UnitTotals[i] = ntohl (UnitTotals[i]);
		}
	}
	InNetworkFormat = 0;		// Flag that data is now in PC format
}


