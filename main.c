#include "game.h"
#include "ft_put.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int ask_restart();

int ask_yes_no();

int main()
{
	t_game	game;
	int		play;
	char*	wordlist_file_name[13];

	wordlist_file_name = "wordlist.txt";
	play = 1;
	while(play)
	{
		init_game(&game);
		start_game(&game, wordlist_file_name);
		while(isfinished_game(&game))
		{
			display_game(&game);
			update_game(&game);	
		}
		display_result_game(&game);
		destroy_game(&game);
		play = ask_restart();
	}
	return EXIT_SUCCESS;
}

int ask_restart()
{
	int res;

	res = ask_yes_no(	"Do you want to restart the game ? (Answear Y or N and press enter)\n", 
						"I did not understand your answear : it must be Y or N (don't forget to press enter)\n");
	return res;
}

int  ask_yes_no(const char* msg, const char* err_msg)
{
	char	answear[2];
	int 	read_char;
	int 	res;

	res = 0;
	ft_putstr(msg);
	while((read_char = read(0, answear, 2)) > 0 && ((toupper(answear[0]) != 'Y' && toupper(answear[0]) != 'N') || answear[1] != '\n'))
	{
		if(answear[1] != '\n')
		{
			while((read_char = read(0, answear, 1)) > 0 && answear[0] != '\n');
		}
		ft_putstr(err_msg);
	}
	if(answear[0] == 'Y' && read_char > 0)
	{
		res = 1;
	}
	return res;
}