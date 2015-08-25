#include "game_display.h"
#include "ft_put.h"

void star_line_display(int length)
{
	int i;

	i = 0;
	while(i < length * 4)
	{
		ft_putchar('*');
		++i;
	}
	ft_putchar('\n');
}

void remaining_try_display(int remaining_try)
{
	ft_putstr("\tREMAINING TRIES : ");
	ft_putchar(remaining_try + '0');
	ft_putchar('\n');
}

void current_word_display(char const* current_word)
{
	int i;

	ft_putstr("\t\t");
	i = 0;
	while(current_word[i] != '\0')
	{
		ft_putchar(current_word[i]);
		ft_putchar(' ');
		++i;
	}
	ft_putchar('\n');
}

void congrats_display()
{
	ft_putchar('\t');
	star_line_display(33 / 4);
	ft_putstr("\t** Congratulation ! You WIN ! **\n");
	ft_putchar('\t');
	star_line_display(33 / 4);
	ft_putchar('\n');
}

static void percentage_line_display(int length)
{
	int i;

	i = 0;
	while(i < length)
	{
		ft_putchar('%');
		++i;
	}
	ft_putchar('\n');
}

void hangman_display(t_game const* game)
{
	ft_putchar('\t');
	percentage_line_display(26);
	ft_putstr("\t%% Sorry, you LOOSE ... %%\n");
	ft_putchar('\t');
	percentage_line_display(26);
	ft_putstr("\nThe word to find was : \n");
	current_word_display(game->expected_word);
	ft_putchar('\n');
}

void hangman_board_display(t_game const* game)
{
	int i;

	i = 0;
	while(game->hangman_board[i] != '\0')
	{
		ft_putchar(game->hangman_board[i]);
		if(i % 13 == 12)
		{
			ft_putchar('\n');
		}
		++i;
	}
}
