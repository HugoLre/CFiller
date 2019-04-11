
// Game Config
#define FIRST_TO_PLAY PLAYER
#define MAX_REC 10
#define MAP_WIDTH 9
#define MAP_HEIGHT 9
#define AI_X (MAP_WIDTH - 1)
#define AI_Y 0
#define PLAYER_X 0
#define PLAYER_Y (MAP_HEIGHT - 1)
#define CLEAR_NBR 4
// General
#define NULL ((void *)0)
#define SCORE_UNSET (-1)
// Colors
#define COLORS_NBRS 6
#define COLOR_RESET "\e[0m"
#define COLORS_CODE {"\e[40m", "\e[43m", "\e[41m", "\e[44m", "\e[42m", "\e[105m"}
#define COLORS_KEY {'B', 'y', 'r', 'b', 'g', 'p'}
#define COLORS_NAME {"black", "yellow", "red", "blue", "green", "pink"}

enum bool
{
    FALSE = 0,
    TRUE
}   bool;

enum player
{
    PLAYER = 1,
    AI
}   player;

// Functions
char *generate_random_map();
char *generate_empty_map();
void print_map(char *map);
char *copy_map(char *map);
void clear_screen();
enum bool is_game_over(char *map);
void player_turn(char *map, char *message);
void ai_turn(char *map, char **message);
char index_of_elem_in_array(char elem, char *array, int array_length);
char ai_play(char *map, char **message);
int count_color(char *map, char color, int x, int y);
void play_color(char *map, char *rec_map, int x, int y, char old_color, char new_color);
void end_game(char *map);