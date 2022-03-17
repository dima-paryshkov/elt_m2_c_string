#include <stdio.h>
#include <stdlib.h>

void getString(char* str)
{
    fprintf(stdout, "Write a string to process\n");
    gets(str);
}




int main()
{
    char* string;
    getString(string);
    return 0;
}
