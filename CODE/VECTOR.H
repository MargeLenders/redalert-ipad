/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef VECTOR_H
#define VECTOR_H

#ifdef NEVER
#ifndef false
#define false 0
#endif
#ifndef true
#define true 1
#endif
#endif

#include	<stdlib.h>
#include	<stddef.h>

#ifndef WW_PLACEMENT_NEW_DEFINED
#define WW_PLACEMENT_NEW_DEFINED
inline void * operator new(size_t , void * pointer) throw() {return(pointer);}
inline void * operator new[](size_t , void * pointer) throw() {return(pointer);}
#endif


/**************************************************************************
**	This is a general purpose vector class. A vector is defined by this
**	class, as an array of arbitrary objects where the array can be dynamically
**	sized. Because is deals with arbitrary object types, it can handle everything.
**	As a result of this, it is not terribly efficient for integral objects (such
**	as char or int). It will function correctly, but the copy constructor and
**	equality operator could be highly optimized if the integral type were known.
**	This efficiency can be implemented by deriving an integral vector template
**	from this one in order to supply more efficient routines.
*/
template<class T>
class VectorClass
{
	public:
		VectorClass(NoInitClass const & ) {};
		VectorClass(unsigned size=0, T const * array=0);
		VectorClass(VectorClass<T> const &);		// Copy constructor.
		virtual ~VectorClass(void);

		T & operator[](unsigned index) {return(Vector[index]);};
		T const & operator[](unsigned index) const {return(Vector[index]);};
		virtual VectorClass<T> & operator =(VectorClass<T> const &); // Assignment operator.
		virtual int operator == (VectorClass<T> const &) const;	// Equality operator.
		virtual int Resize(unsigned newsize, T const * array=0);
		virtual void Clear(void);
		unsigned Length(void) const {return VectorMax;};
		virtual int ID(T const * ptr);	// Pointer based identification.
		virtual int ID(T const & ptr);	// Value based identification.

	protected:

		/*
		**	This is a pointer to the allocated vector array of elements.
		*/
		T * Vector;

		/*
		**	This is the maximum number of elements allowed in this vector.
		*/
		unsigned VectorMax;

		/*
		**	Does the vector data pointer refer to memory that this class has manually
		**	allocated? If so, then this class is responsible for deleting it.
		*/
		unsigned IsAllocated:1;
};


/**************************************************************************
**	This derivative vector class adds the concept of adding and deleting
**	objects. The objects are packed to the beginning of the vector array.
**	If this is instantiated for a class object, then the assignment operator
**	and the equality operator must be supported. If the vector allocates its
**	own memory, then the vector can grow if it runs out of room adding items.
**	The growth rate is controlled by setting the growth step rate. A growth
**	step rate of zero disallows growing.
*/
template<class T>
class DynamicVectorClass : public VectorClass<T>
{
	public:
		DynamicVectorClass(unsigned size=0, T const * array=0);

		// Change maximum size of vector.
		virtual int Resize(unsigned newsize, T const * array=0);

		// Resets and frees the vector array.
		virtual void Clear(void) {ActiveCount = 0;VectorClass<T>::Clear();};

		// Fetch number of "allocated" vector objects.
		int Count(void) const {return(ActiveCount);};

		// Add object to vector (growing as necessary).
		int Add(T const & object);
		int Add_Head(T const & object);

		// Delete object just like this from vector.
		int Delete(T const & object);

		// Delete object at this vector index.
		int Delete(int index);

		// Deletes all objects in the vector.
		void Delete_All(void) {ActiveCount = 0;};

		// Set amount that vector grows by.
		int Set_Growth_Step(int step) {return(GrowthStep = step);};

		// Fetch current growth step rate.
		int Growth_Step(void) {return GrowthStep;};

		virtual int ID(T const * ptr) {return(VectorClass<T>::ID(ptr));};
		virtual int ID(T const & ptr);

	protected:

		/*
		**	This is a count of the number of active objects in this
		**	vector. The memory array often times is bigger than this
		**	value.
		*/
		int ActiveCount;

		/*
		**	If there is insufficient room in the vector array for a new
		**	object to be added, then the vector will grow by the number
		**	of objects specified by this value. This is controlled by
		**	the Set_Growth_Step() function.
		*/
		int GrowthStep;
};


/**************************************************************************
**	This is a derivative of a vector class that supports boolean flags. Since
**	a boolean flag can be represented by a single bit, this class packs the
**	array of boolean flags into an array of bytes containing 8 boolean values
**	each. For large boolean arrays, this results in an 87.5% savings. Although
**	the indexing "[]" operator is supported, DO NOT pass pointers to sub elements
**	of this bit vector class. A pointer derived from the indexing operator is
**	only valid until the next call. Because of this, only simple
**	direct use of the "[]" operator is allowed.
*/
class BooleanVectorClass
{
	public:
		BooleanVectorClass(unsigned size=0, unsigned char * array=0);
		BooleanVectorClass(BooleanVectorClass const & vector);

		// Assignment operator.
		BooleanVectorClass & operator =(BooleanVectorClass const & vector);

		// Equivalency operator.
		int operator == (BooleanVectorClass const & vector);

		// Fetch number of boolean objects in vector.
		int Length(void) {return BitCount;};

		// Set all boolean values to false;
		void Reset(void);

		// Set all boolean values to true.
		void Set(void);

		// Resets vector to zero length (frees memory).
		void Clear(void);

		// Change size of this boolean vector.
		int Resize(unsigned size);

		// Fetch reference to specified index.
		bool const & operator[](int index) const {
			if (LastIndex != index) Fixup(index);
			return(Copy);
		};
		bool & operator[](int index) {
			if (LastIndex != index) Fixup(index);
			return(Copy);
		};

		// Quick check on boolean state.
		bool Is_True(int index) const {
			if (index == LastIndex) return(Copy);
			return(Get_Bit(&BitArray[0], index));
		};

		// Find first index that is false.
		int First_False(void) const {
			if (LastIndex != -1) Fixup(-1);

			int retval = First_False_Bit(&BitArray[0]);
			if (retval < BitCount) return(retval);

			/*
			**	Failure to find a false boolean value in the vector. Return this
			**	fact in the form of an invalid index number.
			*/
			return(-1);
		}

		// Find first index that is true.
		int First_True(void) const {
			if (LastIndex != -1) Fixup(-1);

			int retval = First_True_Bit(&BitArray[0]);
			if (retval < BitCount) return(retval);

			/*
			**	Failure to find a true boolean value in the vector. Return this
			**	fact in the form of an invalid index number.
			*/
			return(-1);
		}

	private:
		void Fixup(int index=-1) const;

		/*
		**	This is the number of boolean values in the vector. This value is
		**	not necessarily a multiple of 8, even though the underlying character
		**	vector contains a multiple of 8 bits.
		*/
		int BitCount;

		/*
		**	This is a referential copy of an element in the bit vector. The
		**	purpose of this copy is to allow normal reference access to this
		**	object (for speed reasons). This hides the bit packing scheme from
		**	the user of this class.
		*/
		bool Copy;

		/*
		**	This records the index of the value last fetched into the reference
		**	boolean variable. This index is used to properly restore the value
		**	when the reference copy needs updating.
		*/
		int LastIndex;

		/*
		**	This points to the allocated bitfield array.
		*/
		VectorClass<unsigned char> BitArray;
};

#endif
