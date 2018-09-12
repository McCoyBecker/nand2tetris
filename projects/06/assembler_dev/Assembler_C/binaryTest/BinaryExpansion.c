#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

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

int main()
{
    int input = 0;
    printf("The input is %d\n", input);
    printf("The output is %s\n", binaryExpansion(input));
    return(0);
}