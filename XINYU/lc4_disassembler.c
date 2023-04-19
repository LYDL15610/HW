/************************************************************************/
/* File Name : lc4_disassembler.c 										*/
/* Purpose   : This file implements the reverse assembler 				*/
/*             for LC4 assembly.  It will be called by main()			*/
/*             															*/
/* Author(s) : tjf and Xinyu Zheng												*/
/************************************************************************/

#include <stdio.h>
#include <string.h>
#include "lc4_memory.h"
//Xinyu Zheng
int reverse_assemble (row_of_memory* memory)
{
  /* binary constants should be proceeded by a 0b as in 0b011 for decimal 3 */
  row_of_memory *c;
  
  while((c = search_opcode(memory,1)) != NULL) {
    char res[32] = {};
    char code[16] = {};
    char Rd[16] = {};
    char Rs[16] = {};
    char Rt[16] = {};
    int cont = c->contents;
    
    
    int firstPart = cont&(7<<9);
    
    int secondPart = cont&(7<<6);
    
    switch(firstPart) {
      case(0<<9):
        strcpy(Rd,"R0,");
        break;
      case(1<<9):
        strcpy(Rd,"R1,");
        break;
      case(2<<9):
        strcpy(Rd,"R2,");
        break;
      case(3<<9):
        strcpy(Rd,"R3,");
        break;
      case(4<<9):
        strcpy(Rd,"R4,");
        break;
      case(5<<9):
        strcpy(Rd,"R5,");
        break;
      case(6<<9):
        strcpy(Rd,"R6,");
        break;
      case(7<<9):
        strcpy(Rd,"R7,");
        break;
      default:
        printf("wrong Rd:%d\n",firstPart);
        return(-1);
    }
    switch(secondPart) {
      case(0<<6):
        strcpy(Rs,"R0,");
        break;
      case(1<<6):
        strcpy(Rs,"R1,");
        break;
      case(2<<6):
        strcpy(Rs,"R2,");
        break;
      case(3<<6):
        strcpy(Rs,"R3,");
        break;
      case(4<<6):
        strcpy(Rs,"R4,");
        break;
      case(5<<6):
        strcpy(Rs,"R5,");
        break;
      case(6<<6):
        strcpy(Rs,"R6,");
        break;
      case(7<<6):
        strcpy(Rs,"R7,");
        break;
      default:
        printf("wrong Rs:%d\n",secondPart);
        return(-1);
    }
    
    //check imm first
    int imm = 1;
    imm = imm<<5;
    if((imm&cont) == imm) {
      strcpy(code,"ADD");
      int immNumber = cont&31;
      sprintf(Rt,"%d",immNumber);
      

    } else {
      int operation = cont&(7<<3);
      int t = cont&(7);
      
      switch(operation) {
        case(0<<3):
          strcpy(code,"ADD");
          break;
        case(1<<3):
          strcpy(code,"MUL");
          break;
        case(2<<3):
          strcpy(code,"SUB");
          break;
        case(3<<3):
          strcpy(code,"DIV");
          break;
        default:
          printf("wrong operation code:%d\n",operation);
          return(-1);
        
      }
      switch(t) {
      case(0):
        strcpy(Rt,"R0");
        break;
      case(1):
        strcpy(Rt,"R1");
        break;
      case(2):
        strcpy(Rt,"R2");
        break;
      case(3):
        strcpy(Rt,"R3");
        break;
      case(4):
        strcpy(Rt,"R4");
        break;
      case(5):
        strcpy(Rt,"R5");
        break;
      case(6):
        strcpy(Rt,"R6");
        break;
      case(7):
        strcpy(Rt,"R7");
        break;
      default:
        printf("wrong Rt:%d\n",t);
        return(-1);
    }
    }
    strcat(res,code);
    strcat(res," ");
    strcat(res,Rd);
    strcat(res," ");
    strcat(res,Rs);
    strcat(res," ");
    strcat(res,Rt);
    //printf("%s\n",res);
  
    
    c->assembly = (char*)malloc(16*sizeof(char));
    if(c->assembly == NULL) {
      return(-1);
    }
    strcpy(c->assembly,res);
    memset(res,0,sizeof(res));
    memset(code,0,sizeof(code));
    memset(Rd,0,sizeof(Rd));
    memset(Rs,0,sizeof(Rs));
    memset(Rt,0,sizeof(Rt));
    
  }
	return 0 ;
}

