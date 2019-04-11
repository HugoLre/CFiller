#include "my.h"
#include <stdio.h>
#include <stdlib.h>

void clear_screen()
{
    char *str;

    str = malloc(sizeof(char) * (CLEAR_NBR + 1));
    for (int i = 0 ; i < CLEAR_NBR ; i++)
        str[i] = '\n';
    str[CLEAR_NBR] = '\0';
    printf("%s", str);
    free(str);
}