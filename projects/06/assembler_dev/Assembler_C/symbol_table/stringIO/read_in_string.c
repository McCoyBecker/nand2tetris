#include <stdio.h>

int main()
{
    char my_string[100];
    printf("Type something!\n");
    fgets(my_string, sizeof(my_string), stdin);
    printf("%s", my_string);
    return(0);
}