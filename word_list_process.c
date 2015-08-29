#include "word_list_process.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //
#include <time.h>
#include <ctype.h>

static int get_element_nb(FILE* wordlist, char c);

static char* extract(FILE* wordlist, int word_index, char c);

static int get_random_index(int element_nb);

static void print_unknown_file();

static void print_empty_file();

static void toupper_str(char* word);

char* pick_word(char const* file_name)
{
	FILE*	wordlist;
	char*	word;
	int		element_nb;
	int		word_index;

	word	= NULL;
	if((wordlist = fopen(file_name, "r")) != NULL)
	{
		if((element_nb = get_element_nb(wordlist, '\n')) != 0)
		{
			word_index = get_random_index(element_nb);
			rewind(wordlist);
			word = extract(wordlist, word_index, '\n');
			fclose(wordlist);
			toupper_str(word);
		}
		else
		{
			print_empty_file();
		}
	}
	else
	{
		print_unknown_file();
	}
	return word;
}

static void toupper_str(char* word)
{
	int i;

	i = -1;
	while(word[++i] != '\0')
	{
		word[i] = toupper(word[i]);
	}
}

static void print_unknown_file()
{
	char const* msg = "The specified file \"wordlist.txt\" was not found\n";

	write(1, msg, strlen(msg));
}

static void print_empty_file()
{
	char const* msg = "The specified file \"wordlist.txt\" is empty\n";

	write(1, msg, strlen(msg));
}
static int get_element_nb(FILE* wordlist, char c)
{
	int		nread;
	char*	buff;
	int		iread;
	int		word;

	buff = NULL;
	buff = malloc(sizeof(*buff));
	iread = 0;
	word = 0;
	while((nread = fread(buff, 1, 1, wordlist)) > 0)
	{
		if(buff[0] == c)
		{
			++iread;
			word = 0;
		}
		else if(buff[0] != '\0' && word == 0)
		{
			word = 1;
		}
	}
	if(word == 1)
	{
		++ iread;
	}
	free(buff);
	return iread;
}

static char* extract(FILE* wordlist, int word_index, char c)
{
	int		nread;
	char*	buff;
	int		iread;
	int		ichar;
	char*	word;
	int		buff_capacity;

	buff = NULL;
	buff = malloc(sizeof(*buff));
	buff_capacity = 1;
	word = NULL;
	word = malloc(sizeof(*word) * 50);
	iread = 0;
	ichar = 0;
	while((nread = fread(buff, 1, buff_capacity, wordlist)) > 0)
	{
		if(buff[0] == c)
		{
			++iread;
		}
		else if(iread == word_index)
		{
			word[ichar++] = buff[0];
		}
		if(iread == word_index + 1)
		{
			break;
		}
	}
	word[ichar] = '\0';
	free(buff);
	return word;
}

static int get_random_index(int element_nb)
{
	int		iword;

	srand(time(NULL));
	iword = rand() % element_nb;
	return iword;
}
