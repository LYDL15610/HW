/************************************************************************/
/* File Name : lc4.c 													*/
/* Purpose   : This file contains the main() for this project			*/
/*             main() will call the loader and disassembler functions	*/
/*             															*/
/* Author(s) : tjf and you												*/
/************************************************************************/

#include <stdio.h>
#include "lc4_memory.h"
#include "lc4_loader.h"
#include "lc4_disassembler.h"

/* program to mimic pennsim loader and disassemble object files */

int main (int argc, char** argv) {
  
/* leave plenty of room for the filename */
  
  char filename[100];

	/**
	 * main() holds the linked list &
	 * only calls functions in other files
	 */

	/* step 1: create head pointer to linked list: memory 	*/
	/* do not change this line - there should no be malloc calls in main() */
	
	row_of_memory* memory = NULL ;

  
  /*
  printf("start insert\n");
  
  add_to_list(&memory,1,0b0001001010000011);
  add_to_list(&memory,3,0b0001001010010011);
  add_to_list(&memory,2,0b0001001010001011);


  row_of_memory* a = search_address(memory,3);
  printf("search address result contents: %x\n",a->contents);
  
  row_of_memory* bbbb;
  bbbb = search_opcode(memory,3);
  if(bbbb!=NULL) {
    printf("search result contents: %x\n",bbbb->contents);
  }
  
  reverse_assemble(memory);
  print_list(memory);

  
  
  printf("address address: %p\n",&memory->address);
  printf("content address: %p\n",&memory->contents);
  printf("assembly address: %p\n",&memory->assembly);
  
  printf("assembly value: %p\n",memory->assembly);
  printf("assembly value: %s\n",memory->assembly);
  */
	/* step 2: determine filename, then open it		*/
	/*   TODO: extract filename from argv, pass it to open_file() */
  printf("step0\n");
  FILE* fp;
  if(argc!=2) {
		printf("error1: usage: ./assembler <assembly_file.asm>\n");
		return(0);
	} else{
		strcpy(filename,argv[1]);
		fp = open_file(filename);		
	}
  printf("step1\n");
	/* step 3: call function: parse_file() in lc4_loader.c 	*/
	/*   TODO: call function & check for errors		*/
  int parse_res = parse_file (fp, &memory);
  fclose(fp);
  printf("step2\n");
	/* step 4: call function: reverse_assemble() in lc4_disassembler.c */
	/*   TODO: call function & check for errors		*/
  int reverse_result = reverse_assemble (memory);
  printf("step3\n");
	/* step 5: call function: print_list() in lc4_memory.c 	*/
	/*   TODO: call function 				*/
  print_list(memory);
  printf("step4\n");
	/* step 6: call function: delete_list() in lc4_memory.c */
	/*   TODO: call function & check for errors		*/
  delete_list(&memory);
  printf("step5\n");
	/* only return 0 if everything works properly */
	return 0 ;
}
