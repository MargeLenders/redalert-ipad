/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef LAYER_H
#define LAYER_H

#include "vector.h"

class ObjectClass;

class LayerClass : public DynamicVectorClass<ObjectClass *>
{
	public:

		//-----------------------------------------------------------------
		void Sort(void);
		bool Submit(ObjectClass const * object, bool sort=false);
		int Sorted_Add(ObjectClass const * const object);


		virtual void Init(void) {Clear();};
		virtual void One_Time(void) {};

		/*
		**	File I/O.
		*/
		bool Load(Straw & file);
		bool Save(Pipe & file) const;
		virtual void Code_Pointers(void);
		virtual void Decode_Pointers(void);
};

#endif
