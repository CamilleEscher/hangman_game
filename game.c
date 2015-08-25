#include "game.h"
#include "game_display.h"
#include "user_input.h"
#include "ft_put.h"
#include <string.h>
#include <stdlib.h>

void init_game(t_game* game)
{
	bzero(game, sizeof(*game));
}

static char* init_current_word(int length)
{
	int i;
	char* new_word;

	new_word = malloc(sizeof(*new_word) * (length + 1));
	i = 0;
	while(i < length)
	{
		new_word[i] = '_';
		++i;
	}
	new_word[i] = '\0';	
	return new_word;
}

static char* init_hangman_board()
{
	char*	board;
	int		i;

	board = malloc(sizeof(*board) * 105);
	board[104] = '\0';
	i = 0;
	while(i < 104)
	{
		if(i > 0 && i < 11)
		{
			board[i] = 'I';
		}
		else if(i > 90 && i < 104)
		{
			board[i] = 'Y';
		}
		else if(i % 13 == 3)
		{
			board[i] = '|';
		}
		else
		{
			board[i] = ' ';
		}
		++i;
	}
	return board;
}

void start_game(t_game* game, char const* expected_word)
{
	game->remaining_try = 7;
	game->expected_word = strdup(expected_word);
	game->current_word = init_current_word(strlen(expected_word));
	game->hangman_board = init_hangman_board();
}

void destroy_game(t_game* game)
{
	free(game->expected_word);
	free(game->current_word);
	free(game->hangman_board);
	bzero(game, sizeof(*game));
}

void display_game(t_game const* game)
{
	int length;

	length = strlen(game->current_word);
	star_line_display(length);
	ft_putchar('\n');
	remaining_try_display(game->remaining_try);
	ft_putchar('\n');
	current_word_display(game->current_word);
	ft_putchar('\n');
	hangman_board_display(game);
	ft_putchar('\n');
	star_line_display(length);
	ft_putchar('\n');
}

void display_result_game(t_game const* game)
{
	display_game(game);
	if(game->won_game == 1)
	{
		congrats_display();
	}
	else
	{
		hangman_display(game);
	}
}

static int check_letter(t_game* game, char const* user_input)
{
	int i;
	int res;

	res = 0;
	i = 0;
	while(game->expected_word[i] != '\0')
	{
		if(game->expected_word[i] == user_input[0] && game->current_word[i] != user_input[0])
		{
			res = 1;
			game->current_word[i] = game->expected_word[i];
		}
		++i;
	}
	return res;
}

static int check_word(t_game* game, char const* user_input)
{
	int res;

	res = 0;
	if(strcmp(game->expected_word, user_input) == 0)
	{
		strcpy(game->current_word, game->expected_word);
		res = 1;
	}
	else if(strlen(user_input) == 1)
	{
		res = check_letter(game, user_input);
	}
	return res;
}

static void is_won_game(t_game* game)
{
	if(strcmp(game->current_word, game->expected_word) == 0)
	{
		game->won_game = 1;
	}
}

static void update_hangman_board(t_game* game)
{
	switch(game->remaining_try)
	{
	case 6 :
		game->hangman_board[21] = '|';
		break;
	case 5 :
		game->hangman_board[34] = '0';
		break;
	case 4 :
		game->hangman_board[47] = '|';
		game->hangman_board[60] = ':';
		break;
	case 3 :
		game->hangman_board[72] = '/';
		break;
	case 2 :
		game->hangman_board[74] = '\\';
		break;
	case 1 :
		game->hangman_board[48] = '\\';
		break;
	case 0 :
		game->hangman_board[46] = '/';
		break;
	default :
		break;
	}
}

void update_game(t_game* game)
{
	char*	user_input;
	int		success;

	user_input = NULL;
	user_input = get_user_input(strlen(game->expected_word));
	success = check_word(game, user_input);
	if(success == 0)
	{
		game->remaining_try -= 1;
	}
	free(user_input);
	update_hangman_board(game);
	is_won_game(game);
}

int isfinished_game(t_game const* game)
{
	int res;

	res = 0;
	if(game->remaining_try > 0 && game->won_game == 0)
	{
		res = 1;
	}
	return res;
}
