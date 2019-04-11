#include "my.h"

char index_of_elem_in_array(char elem, char *array, int array_length)
{
    for (int i = 0 ; i < array_length ; i++)
    {
        if (array[i] == elem)
            return (i);
    }
    return (-1);
}