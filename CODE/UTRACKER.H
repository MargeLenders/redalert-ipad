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
** UnitTracker Class
*/

class	UnitTrackerClass {

	public:

		UnitTrackerClass(int unit_count);
		~UnitTrackerClass(void);

		void 	Increment_Unit_Total (int unit_type);
		void 	Decrement_Unit_Total (int unit_type);
		void	Clear_Unit_Total(void);

		int 	Get_Unit_Total (int unit_type);
		long *Get_All_Totals (void);
		int	Get_Unit_Count (void){return (UnitCount);};

		void	To_Network_Format(void);
		void	To_PC_Format(void);

	private:

		long	*UnitTotals;
		int	UnitCount;
		int	InNetworkFormat;

};
















