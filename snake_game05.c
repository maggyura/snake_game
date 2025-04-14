#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ROWS 10
#define COLUMNS 25


void game_over() {
    while (_kbhit()) {
        //getting rid of previous input
        _getch();
    }

    printf("\nGAME OVER!\nPress Enter to exit...");

    while (1) {
        if (_kbhit()) {
            char key_input = _getch();
            // enter in ascii is 13
            if (key_input == 13)
                break;
        }
    }
    exit(0);
}

void create_area(char area[ROWS][COLUMNS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if ((i == 0 && j == 0) || (i == 0 && j == COLUMNS - 1) || (i == ROWS - 1 && j == 0) || (i == ROWS - 1 && j == COLUMNS - 1))
            {
                area[i][j] = ' ';
            }
            else if (i == 0 && (COLUMNS - 1 > j > 0) || (i == ROWS - 1 && COLUMNS - 1 > j > 0) || (
                           j == 0 && ROWS - 1 > i > 0) || (j == COLUMNS - 1 && ROWS - 1 > i > 0)) {
                area[i][j] = '_';
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
        rand_row = rand()%(ROWS-1) + 1;
        rand_col = rand()%(COLUMNS-1) + 1;
        // checking for it not to be on the position of the snake head
        if (area[rand_row][rand_col] == ' ') {
            break;
        }
    }
    area[rand_row][rand_col] = '*';
}


void update_area(char area[ROWS][COLUMNS],int snake_head_pos[2],int *score, int snake_body[100][2], int *length) {
    int prev_row = snake_head_pos[0];
    int prev_col = snake_head_pos[1];
    char direction_set;

    draw_grid(area);
    printf("GAME SCORE: %d", *score);
    usleep(200000);

    for (int i = *length; i>0;i--) {
        snake_body[i][0] = snake_body[i-1][0];
        snake_body[i][1] = snake_body[i-1][1];
    }

    if (1) {
        snake_body[0][0] = prev_row;
        snake_body[0][1] = prev_col;
    }

    if (kbhit()) {
        char act = getch();
        if (act   == 'w' || act == 'a' || act == 's' || act == 'd') {
            direction_set = act;
        }
    }
    if (direction_set == 'w') {
        if (snake_head_pos[0] != 1) {
            snake_head_pos[0]--;
        }
        else {
            game_over();
        }
    }
    else if (direction_set == 'a') {
        if (snake_head_pos[1] != 1) {
            snake_head_pos[1]--;
        }
        else {
            game_over();
        }
    }
    else if (direction_set == 's') {
        if (snake_head_pos[0] != ROWS-2) {
            snake_head_pos[0]++;
        }
        else {
            game_over();
        }
    }
    else if (direction_set == 'd') {
        if (snake_head_pos[1] != COLUMNS -2) {
            snake_head_pos[1]++;
        }
        else {
            game_over();
        }
    }

    if (area[snake_head_pos[0]][snake_head_pos[1]] == '*') {
        (*score)++;
        (*length)++;
        spawn_food(area, snake_head_pos);
    }
    //clearing old snake parts
    for (int i=0;i<ROWS;i++) {
        for (int j=0;j<COLUMNS;j++) {
            if (area[i][j] == 'O' || area[i][j] == 'o') {
                area[i][j] = ' ';
            }
        }
    }

    area[snake_head_pos[0]][snake_head_pos[1]] = 'O';

    for (int i=0;i< *length;i++) {
        area[snake_body[i][0]][snake_body[i][1]] = 'o';
    }


    //to optimize ram
    fflush(stdout);
    system("cls");
}


int main() {
    int snake_head_row = ROWS/2;
    int snake_head_col = COLUMNS/2;
    int snake_head_pos[2] = {snake_head_row,snake_head_col};
    char area[ROWS][COLUMNS];
    int snake_body[100][2]; //100 body segments each with row and column
    int length = 0;
    int score = 0;

    create_area(area);
    spawn_food(area,snake_head_pos);
    while (1) {
        update_area(area,snake_head_pos, &score, snake_body, &length);
        }
    }