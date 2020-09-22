#ifndef CONNECTFOUR_H__
#define CONNECTFOUR_H__

int player_1(char board[][20], int size, int &coord_j);
int player_2(char board[][20], int size, int &coord_j);
void computer(char board[][20], int size, int coord_i, int coord_j);
void decider(char board[][20], int size, char term, int &coord_i, int &coord_j);
int legality(char board[][20], int size, int coord_i, int coord_j);

int board_is_filled(char board[][20], int size);
void fill_board(char board[][20], int size);
void draw_board(char board[][20], int size);
int win_control(char board[][20], int size, char term, int &last_i, int &last_j, int &type_of_win);

int cont_left(char board[][20], int size, char term, int coord_i, int coord_j);
int cont_bottom_left(char board[][20], int size, char term, int coord_i, int coord_j);
int cont_bottom(char board[][20], int size, char term, int coord_i, int coord_j);
int cont_bottom_right(char board[][20], int size, char term, int coord_i, int coord_j);
int cont_right(char board[][20], int size, char term, int coord_i, int coord_j);

void game_over(char board[][20], int size, int term, int last_i, int last_j, int type_of_win);

int connectfour(char board[][20]);

#endif


