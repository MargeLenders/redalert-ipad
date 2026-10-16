/*
 * Copyright 2025 Electronic Arts Inc.
 *
 * Derived from Electronic Arts Inc.'s public source release for
 * Command & Conquer: Red Alert.
 * Licensed under GPLv3-or-later with additional Electronic Arts terms.
 * Modified for the macOS port, 2026.
 * See LICENSE.md.
 */

/***************************************************************************
 *                                                                         *
 *                 Project Name : Westwood Auto Registration App           *
 *                                                                         *
 *                    File Name : FIELD.H                                  *
 *                                                                         *
 *                   Programmer : Philip W. Gorrow                         *
 *                                                                         *
 *                   Start Date : 04/22/96                                 *
 *                                                                         *
 *                  Last Update : April 22, 1996 [PWG]                     *
 *                                                                         *
 * This module takes care of maintaining the field list used to process    *
 * packets.																						*
 *                                                                         *
 *-------------------------------------------------------------------------*
 * Functions:                                                              *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#ifndef __FIELD_H
#define __FIELD_H

#include <windows.h>
#include <winsock.h>

#define FIELD_HEADER_SIZE	(sizeof(FieldClass) - (sizeof(void *) * 2))

#define TYPE_CHAR						1
#define TYPE_UNSIGNED_CHAR			2
#define TYPE_SHORT					3
#define TYPE_UNSIGNED_SHORT		4
#define TYPE_LONG						5
#define TYPE_UNSIGNED_LONG			6
#define TYPE_STRING					7
#define TYPE_CHUNK					20

class PacketClass;

class FieldClass {

	public:
		friend class PacketClass;
		//
		// Define constructors to be able to create all the different kinds
		// of fields.
		//
		FieldClass(void) {};
		FieldClass(char *id, char data);
		FieldClass(char *id, unsigned char data);
		FieldClass(char *id, short data);
		FieldClass(char *id, unsigned short data);
		FieldClass(char *id, long data);
		FieldClass(char *id, unsigned long data);
		FieldClass(char *id, char *data);
		FieldClass(char *id, void *data, int length);

		void Host_To_Net(void);
		void Net_To_Host(void);

	private:
		char				ID[4];				// id value of this field
		unsigned short	DataType;			// id of the data type we are using
		unsigned short Size;					// size of the data portion of this field
		void  			*Data;				// pointer to the data portion of this field
		FieldClass		*Next;				// pointer to the next field in the field list
};

#endif
