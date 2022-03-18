#include <stdio.h>
#include <stdlib.h>

char *getString(int *lenght)
{
    fprintf(stdout, "Write a string to process\n");

    *lenght = 1;

    char *string = (char *)malloc(*lenght * sizeof(char));
    if (string == NULL)
        return NULL;
    char symbol = getchar();

    while (symbol != '\n')
    {
        string[(*lenght)++ - 1] = symbol;
        string = (char *)realloc(string, *lenght * sizeof(char));
        if (string == NULL)
            return NULL;
        symbol = getchar();
    }
    string[(*lenght)--] = '\0';

    return string;
}

int getCodeSymbolFromNumber(char *string, int l)
{
    char maxChar = '0';
    for (int i = 0; i < l; i++)
        if (string[i] > maxChar)
            maxChar = string[i];

    int notation = (int)maxChar - 47;

    int result = 0;
    for (int i = l - 1, tmp = 1; i >= 0; i--, tmp *= notation)
        result += tmp * ((int)string[i] - 48);

    return result;
}

char *convertAllNumbersToCharacters(char *inputString, const int *lenghtInStr, int *lenghtResultStr)
{
    *lenghtResultStr = 1;
    char *modifiedString = (char *)malloc(*lenghtResultStr);
    if (modifiedString == NULL)
        return NULL;

    for (int i = 0, l = 0, code; i < *lenghtInStr; i++)
    {
        if ('0' <= inputString[i] && inputString[i] <= '9')
            l++;
        else
        {
            if (l > 0)
            {
                code = getCodeSymbolFromNumber(inputString + (i - l), l);
                if (code > 255)
                {
                    fprintf(stdout, "Since the number %d exceeds the maximum ANSI code, it has been replaced by 0\n", code);
                    modifiedString[(*lenghtResultStr)++ - 1] = '0';
                }
                else
                    modifiedString[(*lenghtResultStr)++ - 1] = (char)code;

                modifiedString = (char *)realloc(modifiedString, *lenghtResultStr);
                if (modifiedString == NULL)
                    return NULL;
            }
            modifiedString[(*lenghtResultStr)++ - 1] = inputString[i];
            modifiedString = (char *)realloc(modifiedString, *lenghtResultStr);
            if (modifiedString == NULL)
                return NULL;
            l = 0;
        }
    }
    modifiedString[*lenghtResultStr - 1] = '\0';
    return modifiedString;
}

int main()
{
    char *string;
    int lenght;
    string = getString(&lenght);
    if (string == NULL)
        return -1;

    int lenghtModifiedString;
    char *modifiedString = convertAllNumbersToCharacters(string, &lenght, &lenghtModifiedString);
    if (modifiedString == NULL)
        return -1;

    fprintf(stdout, "%s", modifiedString);

    free(string);
    free(modifiedString);
    return 0;
}
