#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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


	/* step 2: determine filename, then open it		*/
	/*   TODO: extract filename from argv, pass it to open_file() */
	if (argc < 2) {
		printf("Can't Display: %s <filename>\n", argv[0]);
		return 1;
	}

	strcpy(filename,argv[1]);

	printf("Opening file: %s\n", filename);//debug1


	FILE *my_obj_file = open_file(filename);

	if (my_obj_file == NULL){
		printf ("Can't open file: %s\n",filename);
		return 1;
	}

	/* step 3: call function: parse_file() in lc4_loader.c 	*/
	/*   TODO: call function & check for errors		*/
	if (parse_file(my_obj_file, &memory) != 0){
		printf("can't parse file: %s\n",filename);
		return 1;
	}

	//close file
	fclose(my_obj_file);

	/* step 4: call function: reverse_assemble() in lc4_disassembler.c */
	/*   TODO: call function & check for errors		*/
	if (reverse_assemble(memory)!= 0){
		printf("can't reverse assembling memory \n");
		return 1;
	}

	/* step 5: call function: print_list() in lc4_memory.c 	*/
	/*   TODO: call function 				*/
	print_list(memory);

	/* step 6: call function: delete_list() in lc4_memory.c */
	/*   TODO: call function & check for errors		*/
	delete_list(&memory);

	/* only return 0 if everything works properly */
	return 0 ;
}
