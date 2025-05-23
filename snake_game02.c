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

    printf("GAME OVER!\nPress Enter to exit...");

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

void spawn_food() {
    srand(time(NULL));
    int rand_row = 10;
    int rand_col = 10;
    while ()


}

void update_area(char area[ROWS][COLUMNS],int snake_head_pos[2]) {

    int prev_row = snake_head_pos[0];
    int prev_col = snake_head_pos[1];
    char direction_set;
    draw_grid(area);

    usleep(700000);

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


    area[prev_row][prev_col] = ' ';
    area[snake_head_pos[0]][snake_head_pos[1]] = 'O';


    //to optimize ram
    fflush(stdout);
    system("cls");
}


int main() {
    int snake_head_row = ROWS/2;
    int snake_head_col = COLUMNS/2;
    int snake_head_pos[2] = {snake_head_row,snake_head_col};
    char area[ROWS][COLUMNS];
    create_area(area);

    while (1) {
        update_area(area,snake_head_pos);
        }
    }