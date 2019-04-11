#include "my.h"
#include <stdlib.h>
#include <stdio.h>

int max_score(int scores[COLORS_NBRS])
{
    int max_score;

    max_score = 0;
    for (int i = 0 ; i < COLORS_NBRS ; i++)
    {
        if (scores[i] != SCORE_UNSET && scores[i] > max_score)
            max_score = scores[i];
    }
    return (max_score);
}

int min_score(int scores[COLORS_NBRS])
{
    int min_score;

    min_score = MAP_HEIGHT * MAP_WIDTH + 100;
    for (int i = 0 ; i < COLORS_NBRS ; i++)
    {
        if (scores[i] != SCORE_UNSET && scores[i] < min_score)
            min_score = scores[i];
    }
    return (min_score);
}

int ai_rec(char *map, char color, char player, int rec_count)
{
    char *rec_map;
    int scores[COLORS_NBRS];
    char other_player;

    if (rec_count > MAX_REC || is_game_over(map))
        return (count_color(map, map[AI_Y * MAP_WIDTH + AI_X], AI_X, AI_Y));
    map = copy_map(map);
    rec_map = generate_empty_map();
    if (player == PLAYER)
        play_color(map, rec_map, PLAYER_X, PLAYER_Y, map[PLAYER_Y * MAP_WIDTH + PLAYER_X], color);
    else
        play_color(map, rec_map, AI_X, AI_Y, map[AI_Y * MAP_WIDTH + AI_X], color);
    free(rec_map);
    other_player = player == AI ? PLAYER : AI;
    for (char color = 0 ; color < COLORS_NBRS ; color++)
    {
        scores[color] = SCORE_UNSET;
        if (color == map[AI_Y * MAP_WIDTH + AI_X] || color == map[PLAYER_Y * MAP_WIDTH + PLAYER_X])
            continue;
        scores[color] = ai_rec(map, color, other_player, rec_count+1);
    }
    free(map);
    if (player == AI)
        return (max_score(scores));
    return (min_score(scores));
}

char ai_play(char *map, char **message)
{
    int scores[COLORS_NBRS];
    int max_score;
    int max_score_color;
    char *colors_name[COLORS_NBRS] = COLORS_NAME;

    for (int color = 0 ; color < COLORS_NBRS ; color++)
    {
        scores[color] = 0;
        if (color == map[AI_Y * MAP_WIDTH + AI_X] || color == map[PLAYER_Y * MAP_WIDTH + PLAYER_X])
            continue;
        scores[color] = ai_rec(map, color, AI, 1);
    }
    max_score = 0;
    for (int color = 0 ; color < COLORS_NBRS ; color++)
    {
        if (scores[color] > max_score)
        {
            max_score = scores[color];
            max_score_color = color;
        }
    }
    *message = malloc(sizeof(char) * 150);
    snprintf(*message, 150, "AI played %s\nAI max score is %d", colors_name[max_score_color], max_score);
    return max_score_color;
}