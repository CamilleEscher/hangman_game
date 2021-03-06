#ifndef GAME_H
#define GAME_H

/*

*/
typedef struct	s_game
{
	int		remaining_try;
	int		won_game;
	char*	expected_word;
	char*	current_word;
	char*	hangman_board;
	char*	user_input;
}				t_game;

void	init_game(t_game* game);
void	start_game(t_game* game, char const* file_name);
void	check_word(t_game* game);
void	destroy_game(t_game* game);	
void	display_game(t_game const* game);
void	update_game(t_game* game);
int		isfinished_game(t_game const* game);
void	display_result_game(t_game const* game);

#endif
