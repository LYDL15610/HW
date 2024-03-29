#include <stdio.h>
#include <stdlib.h>
#include "lc4_memory.h"

/* declarations of functions that must defined in lc4_loader.c */

FILE* open_file(char* file_name)
{
	FILE* fp = fopen(file_name, "r"); //file pointer

	if (fp == NULL){
		printf("Unable to open file %s \n",file_name);
		return NULL ;
	}
	return fp;

}

int parse_file (FILE* my_obj_file, row_of_memory** memory)
  
/* remember to adjust 16-bit values read from the file for endiannness
 * remember to check return values from fread() and/or fgetc()
 */
  
{
	row_of_memory* cp; //current pointer
	short unsigned int header, address, n;
	
	while (fread(&header, sizeof(header), 1, my_obj_file) == 1){
			header  = (header << 8) | (header >> 8); //endiannness adjust
			fread(&address, sizeof(address),1,my_obj_file);
			fread(&n,sizeof(n),1,my_obj_file);
			address = (address << 8) | (address >> 8); //endiannness adjust
			n = (n << 8) | (n >> 8); //endiannness adjust

			if (header == 0xCADE || header == 0xDADA) {
				for (int i=0; i < n; i++){
					unsigned short int contents;
					fread (&contents, sizeof(contents),1,my_obj_file);
					contents = (contents<<8) | (contents >>8);

					add_to_list(memory,address + i,contents);
					address++; //increase to the next memory

				}
			} else if (header == 0xC3B7) { //SYMBOL header
					//give memory to the label string
					char* label = (char*)malloc((n+1)*sizeof(char));
					fread(label,sizeof(char),n,my_obj_file);
					label[n] = '\0'; //set last one to be NULL

					// Find the specified address and update its label
					row_of_memory* point = search_address(*memory, address);
					if (point != NULL){
						//check to see if there exist any current label
						if (point->label != NULL){
							free (point->label);
						}
						point->label = label; // set the new label
					} else {
						//create a new memory with label
							row_of_memory *newlabel = (row_of_memory *)malloc(sizeof(row_of_memory));
							newlabel->address = address;
							newlabel->label = label;
							newlabel->contents = 0;
							newlabel->assembly = NULL;
							newlabel->next = NULL;

							add_to_list(memory,newlabel->address, newlabel->contents);



						
					}
			}
	}
	//fclose(my_obj_file);
	return 0 ;
}