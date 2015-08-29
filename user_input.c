#include "user_input.h"
#include "ft_put.h"
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

static void get_input(t_game* game, int read_size);

static void format_data(char* user_input);

void get_user_input(t_game* game, int length)
{
	while(game->user_input == NULL)
	{
		get_input(game, length + 1);
	}
	format_data(game->user_input);
}

static void get_input(t_game* game, int read_size)
{
	//char*	user_input;
	int 	readded;
	char	buffer_un;

	//user_input = NULL;
	game->user_input = malloc(sizeof(*(game->user_input)) * read_size);
	ft_putstr("Enter a letter or the complete word and press Enter\n");
	if((readded = read(0, game->user_input, read_size)) > 0)
	{
		if(game->user_input[readded - 1] == '\n')
		{
			game->user_input[readded - 1] = '\0';
		}
		else
		{
			while((readded = read(0, &buffer_un, 1)) != '\n');
		}
	}
	//return user_input;
}

static void format_data(char* user_input)
{
	int i;

	i = -1;
	while(user_input[++i] != '\0')
	{
		user_input[i] = toupper(user_input[i]);
	}
}
