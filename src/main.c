#include "my.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *map = generate_random_map();
    char turn = FIRST_TO_PLAY;
    char *ai_message = NULL;

    while (!is_game_over(map))
    {
        if (turn == PLAYER)
            player_turn(map, ai_message);
        else
        {
            if (ai_message)
                free(ai_message);
            ai_turn(map, &ai_message);
        }
        turn = turn == PLAYER ? AI : PLAYER;
    }
    end_game(map);
    if (ai_message)
        free(ai_message);
    free(map);
    return (0);
}