/* An assembler for the Hack machine. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

/* Declare functions. */

char *binaryExpansion(int input);
void translateLine(char input_line[], FILE *output_file);
void translate(char input[], char output[]);
char *symbolTable(char input[], bool create);

/* A symbol table to handle predefined symbols and user-create symbols for the Hack machine. */

char *symbolTable(char input[], bool create)
{
    char *RAMaddress = NULL;

    if (strcmp(input, "SP"))
    {
        RAMaddress = (char*) calloc(1,sizeof(char));
        memcpy(RAMaddress, "0", 1);
    }

    if (strcmp(input, "LCL"))
    {
        RAMaddress = (char*) calloc(1,sizeof(char));
        memcpy(RAMaddress, "1", 1);
    }

    if (strcmp(input, "ARG"))
    {
        RAMaddress = (char*) calloc(1,sizeof(char));
        memcpy(RAMaddress, "2", 1);
    }

    if (strcmp(input, "THIS"))
    {
        RAMaddress = (char*) calloc(1,sizeof(char));
        memcpy(RAMaddress, "3", 1);
    }

    if (strcmp(input, "THAT"))
    {
        RAMaddress = (char*) calloc(1,sizeof(char));
        memcpy(RAMaddress, "4", 1);
    }
    return(RAMaddress);
}

/* A function to determine the binary expansion of an integer. Returns the binary expansion in string form. */

char *binaryExpansion(int input)
{
    int len = 16;
    char* output = NULL;
    output = (char*) calloc(1, len);
    for (int i = 0; i < len; i++)
    {
        int remainder = (input / (int) pow(2, i)) % 2;
        char c = remainder;
        if (c == 1)
        {
            output[len-i-1] = '1';
        }
        else
        {
            output[len-i-1] = '0';
        }
        input = input - remainder;
    }
    return(output);
}

/* Translation using lookup. */

void translate(char input[], char output[])
{
    for(int i = 0; i < strlen(input); i++)
    {
        /* Destroy comments. */

        if ((input[i] == '/' & input[i+1] == '/') || input[i] == '\0')
        {
            output[i] = '\0';
            break;
        }
        
        /* Search for addressing. If found, replace number with binary expansion. */

        if (input[i] == '@')
        {
            input[i] = '0';
            int number_rep = atoi(input);
            memcpy(output, binaryExpansion(number_rep), 16);
            output[16] = '\n';
            break;
        }

        /* Else, business as usual. */

        else
        {
            output[i] = input[i];
        }
    }
}

/* A wrapper for translating lines. */

void translateLine(char line_to_translate[], FILE *output)
{
    int len_input = strlen(line_to_translate);
    char output_line[17]; // Hack is a 16-bit platform. 17-th spot is for newlines.
    translate(line_to_translate, output_line);
    fputs(output_line, output);
}

/* main */

int main()
{
    /* Specify input file */

    char filename[1000];
    printf("What file should I translate?\n");
    scanf("%s", filename);
    char namecopy[strlen(filename)];
    memcpy(namecopy, filename, strlen(filename));
    
    /* Read in input file, generate output file. */

    FILE *output, *input;
    input = fopen(strcat(filename,".asm"), "r");
    output = fopen(strcat(namecopy, ".hack"), "w+");

    /* Line by line translation. */

    char buffer[1000];
    while (fgets(buffer, 1000, input))
    {
        translateLine(buffer, output);  
    }

    /* Close files, return 0. */
    
    fclose(output);
    fclose(input);
    return(0);
}