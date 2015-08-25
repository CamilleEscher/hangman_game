#include "user_input.h"
#include "ft_put.h"
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

static char* get_input(char* user_input, int read_size);

static char* format_data(char* user_input);

char* get_user_input(int length)
{
	char*	user_input;

	user_input = NULL;
	while(user_input == NULL)
	{
		user_input = get_input(user_input, length + 1);
	}
	user_input = format_data(user_input);
	return user_input;
}

static char* get_input(char* user_input, int read_size)
{
	int 	readded;
	char	buffer_un;

	user_input = malloc(sizeof(*user_input) * read_size);
	ft_putstr("Enter a letter or the complete word and press Enter\n");
	if((readded = read(0, user_input, read_size)) > 0)
	{
		if(user_input[readded - 1] == '\n')
		{
			user_input[readded - 1] = '\0';
		}
		else
		{
			while((readded = read(0, &buffer_un, 1)) != '\n');
			free(user_input);
			user_input = NULL;
		}
	}
	else
	{
		free(user_input);
		user_input = NULL;
	}
	return user_input;
}

static char* format_data(char* user_input)
{
	int i;

	i = 0;
	while(user_input[i] != '\0')
	{
		user_input[i] = toupper(user_input[i]);
		++i;
	}
	return user_input;
}
