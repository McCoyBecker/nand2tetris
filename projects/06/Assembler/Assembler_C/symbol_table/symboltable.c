/* A symbol table implementation with user-defined entries. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Specify the max length of the table. */

#define MAXLENGTH 1000

/* Declare functions. */

void symbolTable();

/* Implement the symbol table. */

void symbolTable()
{
    
}

/* main. */

int main()
{
    /* Print the instruction set to user. */

    printf("Here is the instruction set.\n");
    printf("CREATE foo mem -> associates foo with address mem.\n");
    printf("REMOVE foo -> removes any foo association.\n");
    printf("STOP -> stop creating entries and print table.\n");

    symbolTable();
    return(0);

}