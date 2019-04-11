#include "my.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void print_map(char *map)
{
    char *colors_code[] = COLORS_CODE;
    for (int y = 0 ; y < MAP_HEIGHT ; y++)
    {
        for (int x = 0 ; x < MAP_WIDTH ; x++)
            printf("%s  %s", colors_code[map[y * MAP_WIDTH + x]], COLOR_RESET);
        printf("\n");
    }
}

void random_map(char *map)
{
    srand(time(NULL));
    for (int i = 0 ; i < (MAP_HEIGHT * MAP_WIDTH) ; i++)
    {
        while (TRUE)
        {
            map[i] = rand() % COLORS_NBRS;
            if (i - 1 >= 0 && map[i - 1] == map[i])
                continue;
            if (i - MAP_WIDTH >= 0 && map[i - MAP_WIDTH] == map[i])
                continue;
            break;
        }
    }
    while (map[AI_Y * MAP_WIDTH + AI_X] == map[PLAYER_Y * MAP_WIDTH + PLAYER_X])
        map[AI_Y * MAP_WIDTH + AI_X] = rand() % COLORS_NBRS;
}

char *generate_random_map()
{
    char *map;

    map = malloc(sizeof(char) * MAP_HEIGHT * MAP_WIDTH);
    random_map(map);
    return (map);
}

char *generate_empty_map()
{
    char *map;

    map = malloc(sizeof(char) * MAP_HEIGHT * MAP_WIDTH);
    for (int i = 0 ; i < (MAP_HEIGHT * MAP_WIDTH) ; i++)
        map[i] = 0;
    return (map);
}

char *copy_map(char *map)
{
    char *new_map;

    new_map = malloc(sizeof(char) * MAP_HEIGHT * MAP_WIDTH);
    for (int i = 0 ; i < (MAP_HEIGHT * MAP_WIDTH) ; i++)
        new_map[i] = map[i];
    return (new_map);
}