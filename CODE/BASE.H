/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef BASE_H
#define BASE_H


/****************************************************************************
** This class defines one "node" in the pre-built base list.  Each node
** contains a type of building to build, and the COORDINATE to build it at.
*/
class BaseNodeClass
{
	public:
		BaseNodeClass(void) {};
		BaseNodeClass(StructType building, CELL cell) : Type(building), Cell(cell) {};
		int operator == (BaseNodeClass const & node);
		int operator != (BaseNodeClass const & node);
		int operator > (BaseNodeClass const & node);

		StructType Type;
		CELL Cell;
};


/****************************************************************************
** This is the class that defines a pre-built base for the computer AI.
** (Despite its name, this is NOT the "base" class for C&C's class hierarchy!)
*/
class BaseClass
{
	public:

		/*
		** Constructor/Destructor
		*/
		BaseClass(void) {};
		virtual ~BaseClass() {Nodes.Clear();}

		/*
		** Initialization
		*/
		void Init(void) {House = HOUSE_NONE; Nodes.Clear();}

		/*
		** The standard suite of load/save support routines
		*/
		void Read_INI(CCINIClass & ini);
		void Write_INI(CCINIClass & ini);
		static char *INI_Name(void) {return "Base";}
		bool Load(Straw & file);
		bool Save(Pipe & file) const;
		virtual void Code_Pointers(void) {};
		virtual void Decode_Pointers(void) {};

		/*
		** Tells if the given node has been built or not
		*/
		bool Is_Built(int index) const;

		/*
		** Returns a pointer to the object for the given node
		*/
		BuildingClass * Get_Building(int index) const;

		/*
		** Tells if the given building ptr is a node in this base's list.
		*/
		bool Is_Node(BuildingClass const * obj);

		/*
		** Returns a pointer to the requested node.
		*/
		BaseNodeClass * Get_Node(BuildingClass const * obj);
		BaseNodeClass * Get_Node(int index) { return (&Nodes[index]); }
		BaseNodeClass * Get_Node(CELL cell);

		/*
		** Returns a pointer to the next "hole" in the Nodes list.
		*/
		BaseNodeClass * Next_Buildable(StructType type = STRUCT_NONE);

		/*
		** This is the list of "nodes" that define the base.  Portions of this
		** list can be pre-built by simply saving those buildings in the INI
		** along with non-base buildings, so Is_Built will return true for them.
		*/
		DynamicVectorClass<BaseNodeClass> Nodes;

		/*
		** This is the house this base belongs to.
		*/
		HousesType House;
};


#endif

