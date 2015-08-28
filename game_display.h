#ifndef GAME_DISPLAY_H
#define GAME_DISPLAY_H
#include "game.h"
#include <string.h>

void star_line_display(int length);
void remaining_try_display(int remaining_try);
void current_word_display(char const* current_word);
void congrats_display();
void hangman_display(t_game const* game);
void hangman_board_display(t_game const* game);

#endif
