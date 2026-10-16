/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef REGION_H
#define REGION_H


class RegionClass {
	public:
		RegionClass(void) {Threat = 0;};
		~RegionClass(void) {};
		int operator != (RegionClass const & region) {return memcmp(this, &region, sizeof(RegionClass));};
		int operator == (RegionClass const & region) {return !memcmp(this, &region, sizeof(RegionClass));};
		int operator > (RegionClass const & region) {return memcmp(this, &region, sizeof(RegionClass)) > 0;};
		int operator < (RegionClass const & region) {return memcmp(this, &region, sizeof(RegionClass)) < 0;};

		void Reset_Threat(void) {Threat = 0;};
		void Adjust_Threat(int threat, int neg) {if (neg) Threat -= threat; else Threat+= threat;};
		int Threat_Value(void) const {return Threat;};

	protected:
		long  Threat;
};

#endif
