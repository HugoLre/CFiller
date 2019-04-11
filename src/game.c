#include "my.h"
#include <stdio.h>
#include <stdlib.h>

void mark_zone(char *map, char *rec_map, int x, int y, char color)
{
    int index = y * MAP_WIDTH + x;

    if (rec_map[index] != 0 || map[index] != color)
        return;
    rec_map[index] = 1;
    if (x + 1 < MAP_WIDTH)
        mark_zone(map, rec_map, x+1, y, color);
    if (y + 1 < MAP_HEIGHT)
        mark_zone(map, rec_map, x, y+1, color);
    if (x - 1 >= 0)
        mark_zone(map, rec_map, x-1, y, color);
    if (y - 1 >= 0)
        mark_zone(map, rec_map, x, y-1, color);
}

enum bool is_game_over(char *map)
{
    char *rec_map;
    char ret;

    rec_map = generate_empty_map();
    mark_zone(map, rec_map, AI_X, AI_Y, map[AI_Y * MAP_WIDTH + AI_X]);
    mark_zone(map, rec_map, PLAYER_X, PLAYER_Y, map[PLAYER_Y * MAP_WIDTH + PLAYER_X]);
    ret = TRUE;
    for (int i = 0 ; i < (MAP_HEIGHT * MAP_WIDTH) ; i++)
    {
        if (rec_map[i] != 1)
        {
            ret = FALSE;
            break;
        }
    }
    free(rec_map);
    return (ret);
}

void play_color(char *map, char *rec_map, int x, int y, char old_color, char new_color)
{
    if (map[y * MAP_WIDTH + x] != old_color || rec_map[y * MAP_WIDTH + x] != 0)
        return;
    map[y * MAP_WIDTH + x] = new_color;
    rec_map[y * MAP_WIDTH + x] = 1;
    if (x + 1 < MAP_WIDTH)
        play_color(map, rec_map, x+1, y, old_color, new_color);
    if (x - 1 >= 0)
        play_color(map, rec_map, x-1, y, old_color, new_color);
    if (y + 1 < MAP_HEIGHT)
        play_color(map, rec_map, x, y+1, old_color, new_color);
    if (y - 1 >= 0)
        play_color(map, rec_map, x, y-1, old_color, new_color);
}

void player_turn(char *map, char *message)
{
    char colors_key[] = COLORS_KEY;
    char *colors_name[] = COLORS_NAME;
    char user_input;
    char color_played;
    char *rec_map;

    clear_screen();
    if (message)
        printf("%s\n\n", message);
    print_map(map);
    printf("\n");
    for (int i = 0 ; i < COLORS_NBRS ; i++)
        printf("%c => %s  ", colors_key[i], colors_name[i]);
    while (TRUE)
    {
        printf("\nYour turn: ");
        scanf(" %c", &user_input);
        if ((color_played = index_of_elem_in_array(user_input, colors_key, COLORS_NBRS)) == -1)
            printf("Invalid color code");
        else if (color_played == map[PLAYER_Y * MAP_WIDTH + PLAYER_X] || color_played == map[AI_Y * MAP_WIDTH + AI_X])
            printf("Color played is your color or AI's color");
        else
            break;
    }
    rec_map = generate_empty_map();
    play_color(map, rec_map, PLAYER_X, PLAYER_Y, map[PLAYER_Y * MAP_WIDTH + PLAYER_X], color_played);
    free(rec_map);
}

void ai_turn(char *map, char **message)
{
    char color_played;
    char *rec_map;

    clear_screen();
    print_map(map);
    printf("\nAI is playing ...");
    color_played = ai_play(map, message);
    rec_map = generate_empty_map();
    play_color(map, rec_map, AI_X, AI_Y, map[AI_Y * MAP_WIDTH + AI_X], color_played);
    free(rec_map);
}

int count_color(char *map, char color, int x, int y)
{
    char *rec_map;
    int score;

    rec_map = generate_empty_map();
    mark_zone(map, rec_map, x, y, color);
    score = 0;
    for (int i = 0 ; i < (MAP_WIDTH * MAP_HEIGHT) ; i++)
        score += rec_map[i];
    free(rec_map);
    return (score);

}

void end_game(char *map)
{
    int ai_score;
    int player_score;

    clear_screen();
    print_map(map);
    printf("\n");
    ai_score = count_color(map, map[AI_Y * MAP_WIDTH + AI_X], AI_X, AI_Y);
    player_score = (MAP_HEIGHT * MAP_WIDTH) - ai_score;
    printf("AI: %d\n", ai_score);
    printf("Player: %d\n\n", player_score);
    if (ai_score > player_score)
        printf("AI won !! ;)\n");
    else if (ai_score < player_score)
        printf("Player won ... :'(\n");
    else
        printf("It's a draw :/\n");
}