#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Declare functions. */

void translateLine(char input_line[], FILE *output_file);
void dictionaryLookUp(char input[], char output[], int input_size);

/* An assembler for the Hack machine. */

void dictionaryLookUp(char input[], char output[], int input_size)
{
    
}

void translateLine(char line_to_translate[], FILE *output)
{
    int len_input = strlen(line_to_translate);
    char *output_line = NULL;
    output_line = (char*) calloc(1, len_input);
    dictionaryLookUp(line_to_translate, output_line, len_input);
    printf("%s\n", output_line);
    fputs(output_line, output);
}

int main()
{
    /* Specify input file */
    char filename[1000];
    printf("What file should I translate?\n");
    scanf("%s", filename);

    /* Read in input file, generate output file. */
    FILE *output, *input;
    input = fopen(strcat(filename,".asm"), "r");
    output = fopen("AssembledOutput.asm", "w+");

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