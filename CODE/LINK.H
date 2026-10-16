/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

#ifndef LINK_H
#define LINK_H


/*
**	This implements a simple linked list. It is possible to add, remove, and traverse the
**	list. Since this is a doubly linked list, it is possible to remove an entry from the
**	middle of an existing list.
*/
class LinkClass
{
	public:
		LinkClass(NoInitClass const &) {};
		LinkClass(void) : Next(0), Prev(0) {};
		virtual ~LinkClass(void);

		virtual LinkClass * Get_Next(void) const;
		virtual LinkClass * Get_Prev(void) const;
		virtual LinkClass & Add(LinkClass & object);
		virtual LinkClass & Add_Tail(LinkClass & object);
		virtual LinkClass & Add_Head(LinkClass & object);
		virtual LinkClass & Head_Of_List(void);
		virtual LinkClass & Tail_Of_List(void);
		virtual void Zap(void);
		virtual LinkClass * Remove(void);

		LinkClass & operator=(LinkClass const & link);		// Assignment operator.
		LinkClass(LinkClass const & link);						// Copy constructor.

	private:
		/*
		**	Pointers to previous and next link objects in chain.
		*/
		LinkClass * Next;
		LinkClass * Prev;
};

#endif
