/************************************************************************/
/* File Name : lc4_memory.c		 										*/
/* Purpose   : This file implements the linked_list helper functions	*/
/* 			   to manage the LC4 memory									*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "lc4_memory.h"


/*
 * adds a new node to a linked list pointed to by head
 */
int add_to_list (row_of_memory** head,
		 short unsigned int address,
		 short unsigned int contents)
{

    /* check to see if there is already an entry for this address and update the contents.  no additional steps required in this case */
    
    /* allocate memory for a single node */

	/* populate fields in newly allocated node w/ address&contents, NULL for label and assembly */
	/* do not malloc() storage for label and assembly here - do it in parse_file() and reverse_assemble() */

	/* if *head is NULL, node created is the new head of the list! */

	/* otherwise, insert node into the list in address ascending order */

	/* return 0 for success, -1 if malloc fails */
  
  row_of_memory *newNode;
  newNode = malloc(sizeof(row_of_memory));
  if(newNode == NULL) {
    return -1;
  }
  newNode->address = address;
  newNode->contents = contents;
  newNode->label = NULL;
  newNode->assembly = NULL;
  newNode->next = NULL;


  if(*head == NULL) {
    /*
    *head = malloc(sizeof(row_of_memory));
    if(*head == NULL){
      return -1;
    }*/
    *head = newNode;
    return 0;
  }
  
  

  row_of_memory *p,*n;
  //aaaa
  /*
  p = *head;
  while(p->next!=NULL) {
    p = p->next;
  }
  p->next = newNode;
  return 0;
  */
  //aaaa
  p = *head;
  if(p->address > address) {
    newNode->next = *head;
    *head = newNode;
    return 0;
  }


  while(p->next!=NULL) {
    if(p->next->address<address) {
      p = p->next;
    } else{
      break;
    }
  }
  

  newNode->next = p->next;
  p->next = newNode;
	return 0 ;
}



/*
 * search linked list by address field, returns node if found
 */
row_of_memory* search_address (row_of_memory* head,
			       short unsigned int address )
{
	/* traverse linked list, searching each node for "address"  */

	/* return pointer to node in the list if item is found */

	/* return NULL if list is empty or if "address" isn't found */
  row_of_memory *p;
  p = head;
  while(p!=NULL) {
    if(p->address == address) {
      return p;
    }
    if(p->address>address) {
      break;
    }
    p = p->next;

  }
  

	return NULL ;
}

/*
 * search linked list by opcode field, returns node if found
 */
row_of_memory* search_opcode  (row_of_memory* head,
				      short unsigned int opcode  )
{
    /* opcode parameter is in the least significant 4 bits of the short int and ranges from 0-15 */
		/* see assignment instructions for a detailed description */
    
    /* traverse linked list until node is found with matching opcode in the most significant 4 bits
	   AND "assembly" field of node is NULL */

	/* return pointer to node in the list if item is found */

	/* return NULL if list is empty or if no matching nodes */
  
  
  row_of_memory *p;
  p = head;
  
  while(p!=NULL) {
    
    int a = p->contents;
    a = a>>12;
    
    if(a == opcode && p->assembly == NULL) {
      return p;
    }

    p = p->next;
  }
  
	return NULL ;
}


void print_list (row_of_memory* head )
{
	/* make sure head isn't NULL */

	/* print out a header */
    
    /* don't print assembly directives for non opcode 1 instructions if you are doing extra credit */

	/* traverse linked list, print contents of each node */
  
  row_of_memory *start;
  if(head == NULL) {
    return;
  }
  
  
  printf("%-20s%-20s%-20s%-20s\n","<label>","<address>","<contents>","<assembly>");
  for (start = head;start!=NULL;start = start->next) {
    printf("%-20s%-20.04x%-20.04x%-20s\n",start->label,start->address,start->contents,start->assembly);
    
  }

	return ;
}

/*
 * delete entire linked list
 */
int delete_list    (row_of_memory** head )
{
	/* delete entire list node by node */
	/* set the list head pointer to NULL upon deletion */
  row_of_memory *clear,*n;
  clear = *head;
  if(clear->assembly!=NULL) {
    free(clear->assembly);
  }
  if(clear->label!=NULL) {
    free(clear->label);
  }
  while(clear->next != NULL) {
    n = clear->next;
    clear->next = n->next;
    if(n->assembly!=NULL) {
      free(n->assembly);
    }
    if(n->label!=NULL) {
    free(n->label);
    }
    free(n);
  }
  
  free(*head);
	return 0 ;
}
