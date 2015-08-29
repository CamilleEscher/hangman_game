#include "word_list_process.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h> //

static int get_element_nb(FILE* wordlist, char c);

static char* extract(FILE* wordlist, int word_index, char c);

static int get_random_index(int element_nb);

static void print_unknown_file(char const* file_name);

static void print_empty_file(char const* file_name);

char* pick_word(char const* file_name)
{
	FILE*	wordlist;
	char*	word;
	int		element_nb;
	int		word_index;

	word	= NULL;
	wordlist = NULL;
	if((wordlist = fopen(file_name, "r")) != NULL)
	{
		if((element_nb = get_element_nb(wordlist, '\n')) != 0)
		{
			word_index = get_random_index(element_nb);
			rewind(wordlist);
			word = extract(wordlist, word_index, '\n');
		}
		else
		{
			print_empty_file(file_name);
		}
		fclose(wordlist);
	}
	else
	{
		print_unknown_file(file_name);
	}
	return word;
}

static void print_unknown_file(char const* file_name)
{
	char const* msg = "The specified file \"";
	char const* end_msg = "\" was not found\n";
	
	write(1, msg, strlen(msg));
	write(1, file_name, strlen(file_name));
	write(1, end_msg, strlen(end_msg));
}

static void print_empty_file(char const* file_name)
{
	char const* msg = "The specified file \"";
	char const* end_msg = "\" is empty\n";
	
	write(1, msg, strlen(msg));
	write(1, file_name, strlen(file_name));
	write(1, end_msg, strlen(end_msg));
}

static int get_element_nb(FILE* wordlist, char c)
{
	int		nread;
	char*	buff;
	int		iread;
	int		word_length;

	buff = NULL;
	buff = malloc(sizeof(*buff));
	iread = 0;
	word_length = 0;
	while((nread = fread(buff, 1, 1, wordlist)) > 0)
	{
		if((buff[0] == c || buff[0] == '\0') && word_length > 0)
		{
			++iread;
			word_length = 0;
		}
		else if(buff[0] != '\0' && ((buff[0] >= 'A' && buff[0] <= 'z') || (buff[0] == '-' && word_length > 0)))
		{
			++word_length;
		}
	}
	free(buff);
	return iread;
}

static char* extract(FILE* wordlist, int word_index, char c)
{
	int		nread;
	char*	buff;
	int		iread;
	int		word_length;
	char*	word;

	buff = NULL;
	buff = malloc(sizeof(*buff));
	word = NULL;
	word = malloc(sizeof(*word) * 50);
	iread = 0;
	word_length = 0;
	while((nread = fread(buff, 1, 1, wordlist)) > 0)
	{
		if(buff[0] == c && word_length > 0)
		{
			++iread;
			if(iread > word_index)
			{
				break;
			}
			word_length = 0;
		}
		else if(buff[0] != '\0' && ((buff[0] >= 'A' && buff[0] <= 'z') || buff[0] == '-'))
		{
			if(iread == word_index)
			{
				word[word_length] = toupper(buff[0]);
			}
			++word_length;
		}
	}
	word[word_length] = '\0';
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
