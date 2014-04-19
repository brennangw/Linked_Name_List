/*****************************************************************
 * Brennan Wallace                                               *
 * Box:  4775                                                    *
 * Supplemental Problem 5 for CSC 161                            *
 * Assignment for Tuesday, May 7                                 *
 *****************************************************************/

/* ***************************************************************
 *
 *   Written/online sources used:                                *
 *   -->The C programming Language
 *		By Brian W. Kernighan and Dennis M. Ritchie.
 *   -->stack overflow (Website)
 *		1: Pointers
 *		stackoverflow.com/questions/346730/how-to
 *		-work-with-pointer-to-pointer-to-structure-in-c
 *		gnu.org/software/libc/manual/html_node/Line-Input.html
 *		2: remove new line character in c
 *		stackoverflow.com/questions/2396623/
 * 		remove-new-line-character-in-c
 *	 -->GNU.org (website)
 *		1: line input
 *		gnu.org/software/libc/manual/html_node/Line-Input.html
 *		2. strnig functions
 *		gnu.org/software/libc/manual/html_node/Copying-and-
 *		Concatenation.html
 *   -->Professor Henery Walker's 161 Website at cs.grinnell.edu
 *****************************************************************/


/* A program shell  to maintain a linked list of names */

/* library for standard I/O */
#include <stdio.h>

/* library for memory allocation */
#include <stdlib.h>

#include <string.h>

/* Maximum length of names */
#define strMax 20

struct node
{
	char data [strMax];
	struct node * next;
};



/* function prototypes, listed in alphabetical order */

void addName(struct node ** firstPtr);
/* pre-condition:  firstPtr points to the pointer
 designating the head of a list
 post-condition:  a name is read and
 inserted into the list at a designated place
 */

void print(struct node * first);
/* pre-condition:  first designates the first node of a list
 post-condition:  The items on the list are printed from first to last
 the list itself is unchanged
 */

void deleteAllSubsquentDuplicateNodes (struct node * selection);
/* pre-condition:  selection designates a node of a linked list
 post-condition:  all nodes are removed from the list that have the same name/data 
 as the selected one.
 */

void addNamesFromFile (struct node ** first);
/* pre-condition:  first designates the first node of a list
 post-condition:  the program asks the user for a file name
 names from individual lines of the file are inserted
 at the end of the original list
 */

void removeDuplicates (struct node * first);
/* pre-condition:  first designates the first node of a list
 post-condition:  each name on the list appears only once (no duplicate names)
 when duplicates occur on the original list,
 only the first occurence remains after processing
 */

void putFirst (struct node ** firstPtr);
/* pre-condition:  first designates the first node of a list
 post-condition:  a name is read, located on the list,
 and placed at the beginning of the list
 */

int main (void) {
	/* program to coordinate the menu options and calls the requested function */
	
	struct node * first = NULL;   /* pointer to the first list item */
	char option[strMax];          /* user response to menu selection */
	
	printf ("Program to Maintain a List of Names\n");
	
	while (1) {
		/* print menu options */
		printf ("Options available\n");
		printf ("I - Insert a name (from the keyboard) into the list\n");
		printf ("P - Print the names on the list\n");
		printf ("R - Read a sequence of names from a file onto the list\n");
		printf ("D - Remove duplicate names (leaving only the first occurence)\n");
		printf ("F - Move an item to the front of the list\n");
		printf ("Q - Quit\n");
		
		/* determine user selection */
		printf ("Enter desired option: ");
		scanf ("%s", option);
		
		switch (option[0])
		{ case 'I':
			case 'i':
				addName(&first);
				break;
			case 'P':
			case 'p':
				print(first);
				break;
			case 'R':
			case 'r':
				addNamesFromFile(&first);
				break;
			case 'D':
			case 'd':
				removeDuplicates(first);
				break;
			case 'f':
				putFirst(&first);
				break;
			case 'Q':
			case 'q':
				printf ("Program terminated\n");
				return 0;
				break;
			default: printf ("Invalid Option - Try Again!\n");
				continue;
		}
	}
}


void addName(struct node ** firstPtr) {
	/* pre-condition:  firstPtr points to the pointer designating the head of a list
	 post-condition:  a name is read and
	 inserted into the list at a designated place
	 */
	
	char oldName [strMax];
	struct node * newNode = (struct node *)malloc(sizeof(struct node));
	struct node * listPtr;
	struct node * prevPtr;
	
	printf ("Enter name to be inserted into list: ");
	scanf ("%s", newNode->data);
	
	if (*firstPtr == NULL) {
		/* insert name's node at start of list */
		newNode->next = *firstPtr;
		*firstPtr = newNode;
	}
	
	else {
		printf ("Enter old name which new name should preceed, \n");
		printf ("or enter ? if new name should be placed last\n");
		scanf ("%s", oldName);
		
		if (strcmp (oldName, (*firstPtr)->data) == 0) {
			/* insert name's node at start of list */
			newNode->next = *firstPtr;
			*firstPtr = newNode;
		}
		else {
			/* insert name's node after start of the list */
			
			/* start at beginning of list */
			listPtr = (*firstPtr)->next;  /* the current node to search */
			prevPtr = *firstPtr;          /* the node behind listPtr */
			
			while (listPtr && (strcmp (oldName, listPtr->data) != 0)) {
				prevPtr = listPtr;
				listPtr = prevPtr->next;
			}
			
			newNode->next = prevPtr->next;
			prevPtr->next = newNode;
		}
	}
	printf ("%s inserted into the list\n\n", newNode->data);
}

void print(struct node * first){
	/* pre-condition:  first designates the first node of a list
	 post-condition:  The items on the list are printed from first to last
	 the list itself is unchanged
	 */
	struct node * listElt = first;
	printf ("The names on the list are:\n\n");
	
	while (listElt) {
		printf ("%s\n", listElt->data);
		listElt = listElt->next;
	}
	
	printf ("\nEnd of List\n\n");
}

void addNamesFromFile (struct node ** first)
{
	/* pre-condition:  first designates the first node of a list
	 post-condition:  the program asks the user for a file name
	 names from individual lines of the file are inserted
	 at the end of the original list
	 */
	char fileName [strMax];
	FILE *fileVar;
	int len;
	printf ("Enter file name: ");
	scanf ("%s", fileName);
	fileVar = fopen (fileName, "r");
	if (fileVar == NULL)
		{
		printf("file does not exist\n");
		}
	else
		{
	
	//processFile (&fileVar, first);
	

		char * inputLine = (char *)malloc(strMax * sizeof('a'));
		struct node * current;
		if ((*first) == NULL)
			{
			current = (struct node *)malloc(sizeof(struct node));
			(*first) = current;
			}
		else
			{
			current = (*first);
			//go to the end of the list
			while (current -> next != NULL)
				{
				current = current->next;
				}
			}
		do {
			if (fgets(inputLine, strMax, fileVar) == NULL)
				{
				break;
				}
			
			struct node * newNode = (struct node *)malloc(sizeof(struct node));
			current->next = newNode;
			len = strlen(inputLine);
			
			//remove newline character 
			if( inputLine[len-1] == '\n' )
				{inputLine[len-1] = 0;}
			
			strcpy (newNode->data, inputLine);
			current = current->next;
			}while (inputLine != NULL);
		
		}
}

void initialize (char file_name[], FILE **filev)
/* procedure to initialize all program variables */
{	printf ("Enter file name: ");
	scanf ("%s", file_name);
	(*filev) = fopen (file_name, "r");
}

void removeDuplicates (struct node * first) {
	/* pre-condition:  first designates the first node of a list
	 post-condition:  each name on the list appears only once (no duplicate names)
	 when duplicates occur on the original list,
	 only the first occurence remains after processing
	*/
	
	
	 if (first == NULL)
		 {
		 printf("list is empty. No work to be done.\n");
		 }
	if (first->next == NULL)
		{
		printf("1 item in list. No work to be done.\n");
		}
	else
		{
		struct node * current = first;
		while (current != NULL)
			{
			deleteAllSubsquentDuplicateNodes (current);
			current = current -> next;
			}
		}
}
void deleteAllSubsquentDuplicateNodes (struct node * selection) {
/* pre-condition:  selection designates a node of a linked list
 post-condition:  all nodes are removed from the list that have the same name/data
 as the selected one.
*/

	struct node * previous = selection;
	struct node * current = previous->next;
	while (current != NULL)
		{
		if (strcmp(current->data, selection->data) == 0)
			{
			previous->next = current->next;
			current = previous->next;
			}
		else
			{
			previous = current;
			current = current->next;
			}
		}
}



void putFirst (struct node ** firstPtr) {
	/* pre-condition:  first designates the first node of a list
	 post-condition:  a name is read, located on the list,
	 and placed at the beginning of the list
	 */
	struct node * listPtr;
	struct node * prevPtr;
	
	if ((*firstPtr) == NULL)
		printf("list is empty. No work to be done.\n");
	else if((*firstPtr)->next == NULL)
		printf("1 item in list. No work to be done.\n");
	else
		{
		char name[strMax];
		printf("What Node To Move Forward:\n");
		scanf ("%s", name);
		if  (strcmp (name, (*firstPtr)->data) == 0)
			printf("it is already at the front\n");
		else
			{
			
			
			listPtr = (*firstPtr)->next;  /* the current node to search */
			prevPtr = *firstPtr;          /* the node behind listPtr */
			
			while ((strcmp (name, listPtr->data) != 0))
				{
				prevPtr = listPtr;
				listPtr = prevPtr->next;
				if (listPtr == NULL) //if this is true than the name is not in the list
					{
					printf("not found\n");
					return;				
					}

				}
			
		//moving pointers so the selected node is "first"
		prevPtr->next = listPtr->next;
		listPtr->next = (*firstPtr);
		(*firstPtr) = listPtr;
		}
		}

}




