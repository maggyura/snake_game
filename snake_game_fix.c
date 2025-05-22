#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ROWS 10
#define COLUMNS 25


void game_over(int snake_head_pos[2], int *length, int *score) {
    while (_kbhit()) {
        //getting rid of previous input
        _getch();
    }

    printf("\nGAME OVER!\nPress Enter to exit...");
    printf("\n");
    printf("\nOr Space to try again!");

    //Enter and Space bar situations
    while (1) {
        if (_kbhit()) {
            char key_input = _getch();
            // enter in ascii is 13
            if (key_input == 13)
                exit(0);
            //space bar in ascii is 32
            else if (key_input==32) {
                snake_head_pos[0] = ROWS/2;
                snake_head_pos[1] = COLUMNS/2;
                *length = 0;
                *score = 0;
                break;
            }
        }
    }

}

void create_area(char area[ROWS][COLUMNS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            // went with the decision to make corners empty char
            if ((i == 0 && j == 0) || (i == 0 && j == COLUMNS - 1) || (i == ROWS - 1 && j == 0) || (i == ROWS - 1 && j == COLUMNS - 1))
            {
                area[i][j] = ' ';
            }
            else if (i == 0 && (COLUMNS - 1 > j > 0) || (i == ROWS - 1 && COLUMNS - 1 > j > 0) || (
                           j == 0 && ROWS - 1 > i > 0) || (j == COLUMNS - 1 && ROWS - 1 > i > 0)) {
                area[i][j] = '-';
            } else {
                area[i][j] = ' ';
            }
        }
    }
}

void draw_grid(char area[ROWS][COLUMNS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            printf("%c", area[i][j]);
        }
        printf("\n");
    }
}

void spawn_food(char area[ROWS][COLUMNS], int snake_head_pos[2]) {
    srand(time(NULL));
    int rand_row = 0;
    int rand_col = 0;
    while (1) {
        rand_row = rand()%(ROWS-2) + 1;
        rand_col = rand()%(COLUMNS-2) + 1;
        // checking for it not to be on the position of the snake head
        if (area[rand_row][rand_col] == ' ') {
            break;
        }
    }
    area[rand_row][rand_col] = '*';
}


void init_game(char area[ROWS][COLUMNS],int snake_head_pos[2],int *score, int snake_body[100][2], int *length) {
    //Stores the current position of the snake's head before it moves.
    int prev_row = snake_head_pos[0];
    int prev_col = snake_head_pos[1];

    //it is static char so it doesn't reset to 'w' every time init_game() is called(it gets called every move). It will store the last value of direction.
    static char direction_set = 'w';

    draw_grid(area);
    printf("GAME SCORE: %d", *score);
    usleep(250000);

    // This `for` loop shifts the position of every segment to the row and column to the segment in front of it.
    // It will change the segments by the length of the body.
    for (int i = *length; i>0;i--) {
        snake_body[i][0] = snake_body[i-1][0];
        snake_body[i][1] = snake_body[i-1][1];
    }

    //For the segment right after the head. Stores its value and uses it in the snippet above
    // fix: if(1) statement removed. It served no purpose
    snake_body[0][0] = prev_row;
    snake_body[0][1] = prev_col;

    // Sets char act to the direction set depending on which key was pressed
    if (kbhit()) {
        char act = getch();
        // fix: fixed mistype
        if ((act   == 'w' && direction_set!='s') || (act == 'a' && direction_set != 'd')||
            (act == 's' && direction_set != 'w') ||(act=='d'&&direction_set!='a') ){
            direction_set = act;
        }
    }

    //Handling the game in case snake stumbles into its own tail. Triggering game_over function.
    if (area[snake_head_pos[0]][snake_head_pos[1]] == 'o') {
        game_over(snake_head_pos, length, score);
    }

    // Snake's movement
    if (direction_set == 'w') {
        //checking if it will not hit a wall
        if (snake_head_pos[0] != 1) {
            snake_head_pos[0]--;
        }
        else {
            game_over(snake_head_pos, length, score);
        }
    }
    else if (direction_set == 'a') {
        if (snake_head_pos[1] != 1) {
            snake_head_pos[1]--;
        }
        else {
            game_over(snake_head_pos, length, score);
        }
    }
    else if (direction_set == 's') {
        if (snake_head_pos[0] != ROWS-2) {
            snake_head_pos[0]++;
        }
        else {
            game_over(snake_head_pos, length, score);
        }
    }
    else if (direction_set == 'd') {
        if (snake_head_pos[1] != COLUMNS -2) {
            snake_head_pos[1]++;
        }
        else {
            game_over(snake_head_pos, length, score);
        }
    }

    //If the food is eaten
    if (area[snake_head_pos[0]][snake_head_pos[1]] == '*') {
        (*score)++;
        (*length)++;
        spawn_food(area, snake_head_pos);
    }

    //clearing old snake parts. It checks the whole grid looking for snake parts and disposes of them.
    for (int i=0;i<ROWS;i++) {
        for (int j=0;j<COLUMNS;j++) {
            if (area[i][j] == 'O' || area[i][j] == 'o') {
                area[i][j] = ' ';
            }
        }
    }
    // spawning a head.
    area[snake_head_pos[0]][snake_head_pos[1]] = 'O';

    // spawning body parts by length of the body.
    for (int i=0;i< *length;i++) {
        area[snake_body[i][0]][snake_body[i][1]] = 'o';
    }


    //Makes sure that score and grid appear before screen cleans.
    fflush(stdout);
    system("cls");
}


int main() {
    int snake_head_row = ROWS/2;
    int snake_head_col = COLUMNS/2;
    int snake_head_pos[2] = {snake_head_row,snake_head_col};
    char area[ROWS][COLUMNS];
    int snake_body[100][2]; //100 body segments each with position of the segments.
    int length = 0;
    int score = 0;

    create_area(area);
    spawn_food(area,snake_head_pos);
    while (1) {
        init_game(area,snake_head_pos, &score, snake_body, &length);
        }
    }