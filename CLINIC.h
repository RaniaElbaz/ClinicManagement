#ifndef CLINIC
#define CLINIC

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "STD_TYPES.h"

#define BUFFER 100 //MAX SIZE OF INPUT
#define PASSWORD 1234 //Default password
#define TRY 3 //max number of tries
#define MAX_PT 100//max number of patients' records in the clinic
#define SLOTS 5 //max number of reservation slots
#define HOLD printf("\n\t\tpress any key to continue...\n");\
			 getch() //holds screen
#define DONE printf("\n\t\t----DONE----")

typedef struct patient{
	u8 *fname, *lname, gender;
	u32 ID, age, label;
	struct patient* next;
}record;

/*
	Description: create a linked list to reserve the records in (nodes) 
	Input:		 head: pointer to pointer to node of record type, head of the list
*/
void createList(record**);

/*
	Description: read string input from user
	Output:		 input: pointer to array of characters, holds the input from the user

*/
u8* readLine(void);

/*
	Description: search for patient's ID if it has already been reserved
	Input:		 list: pointer to node of record type, head of the list
				 id:   unsigned int 32, patient's ID
    Output:		 1- true if ID exists
				 2- false if ID does not exist
*/
bool FindID(record*,u32);

/*
	Description: add new node (patient's record) to the list only if the ID is not reserved before
	Input:		 list_ref: pointer to pointer to node of record type, head of the list
				 id:   unsigned int 32, patient's ID
*/
void addP(record**,u32);

/*
	Description: edit an existing record 
	Input:		 list_ref: pointer to pointer to node of record type, head of the list
				 id:   unsigned int 32, patient's ID
*/
void editP(record**,u32);

/*
	Description: check the daily reservation slots and print which is free
	Input:		 n: pointer to node of record type, head of the list
*/
void check(record*);

/*
	Description: edit the required node (appointment) to be reserved
	Input:		 list: pointer to node of record type, head of the list
				 id:   unsigned int 32, patient's ID
	pre-condition:	1-the slot has not been reserved before
					2-ID has a record before
*/
void res(record*,u32);

/*
	Description:	edit the required node (appointment) to be free
	Input:		 	list: pointer to node of record type, head of the list
					id:   unsigned int 32, patient's ID
	pre-condition:	1-the slot has been reserved before
					2-ID has a record before		 
*/
void cancel(record*,u32);

/*
	Description:	print all the daily reservations
	Input:		 	n: pointer to node of record type, head of the list
*/
void printresv(record*);

/*
	Description:	print all the patients' records
	Input:		 	n: pointer to node of record type, head of the list
					c: unsigned char, number of records(nodes) required
*/
void printList(record*,u8);

#endif