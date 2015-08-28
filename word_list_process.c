#include "word_list_process.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //
#include <time.h>
#include <ctype.h>

static char* get_file_content(char* content, FILE* wordlist);

static char* reallocate(char* content, int content_capacity, int buff_capacity);

static void	buffer_strcpy(char* content, char const* buff, int total_readded, int readded);

static char** split_content(char* content, char c);

static int get_element_nb(char* content, char c);

static char* extract_str(char* str, int start, int end);

static char** ptr_array_reallocate(char** word_array, int element_nb, int size_added);

static char* choose_word(char** word_array);

char* pick_word(char const* file_name)
{
	FILE*	wordlist;
	char*	content;
	char*	word;
	char**	word_array;
	int		i;

	content		= NULL;
	word_array	= NULL;
	word		= NULL;
	wordlist	= fopen(file_name, "r");
	content		= get_file_content(content, wordlist);
	word_array	= split_content(content, '\n');
	word		= choose_word(word_array);
	fclose(wordlist);
	free(content);
	i = -1;
	while(word_array[++i] != NULL)
	{
		free(word_array[i]);
	}
	free(word_array);
	i = -1;
	while(word[++i] != '\0')
	{
		word[i] = toupper(word[i]);
	}
	return word;
}

static char* get_file_content(char* content, FILE* wordlist)
{
	char*	buff;
	int		buff_capacity;
	int		total_readded;
	int		readded;
	int		content_capacity;
	
	buff_capacity = 512;
	content_capacity = 0;
	buff = NULL;
	buff = malloc(sizeof(*buff) * buff_capacity);
	total_readded = 0;
	while((readded = fread(buff, 1, buff_capacity, wordlist)) > 0)
	{
		while(total_readded + readded > content_capacity)
		{
			content = reallocate(content, content_capacity, buff_capacity);
			content_capacity += buff_capacity;
		}
		buffer_strcpy(content, buff, total_readded, readded);
		total_readded += readded;
	}
	content[total_readded] = '\0';
	free(buff);
	return content;
}

static char* reallocate(char* content, int content_capacity, int buff_capacity)
{
	char* temp;

	temp = NULL;
	temp = malloc(sizeof(*temp) * (content_capacity + buff_capacity));
	strncpy(temp, content, content_capacity);
	free(content);
	return temp;
}

static void	buffer_strcpy(char* content, char const* buff, int total_readded, int readded)
{
	int i;

	i = 0;
	while(i < readded)
	{
		content[total_readded + i] = buff[i];
		++i;
	}
}

static char** split_content(char* content, char c)
{
	char**	word_array;
	char*	word;
	int		word_array_element_nb;
	int		i;
	int		count;
	int		word_index;

	word = NULL;
	word_array = NULL;
	count = 0;
	word_array_element_nb = get_element_nb(content, c);
	word_array = ptr_array_reallocate(word_array, 0, word_array_element_nb + 1);
	i = -1;
	word_index = 0;
	while(content[++i] != '\0')
	{
		if(content[i] == c)
		{
			word = extract_str(content, word_index, i - 1);
			word_array[count++] = word;
			word = NULL;
			word_index += (i - word_index) + 1;
		}
		else if(content[i + 1] == '\0')
		{
			word = extract_str(content, word_index, i);
			word_array[count++] = word;
			word = NULL;
		}
	}
	word_array[count] = NULL;
	return word_array;
}

static int get_element_nb(char* content, char c)
{
	int		element_nb;
	int		i;

	element_nb = 0;
	i = -1;
	while(content[++i] != '\0')
	{
		if(content[i] == c || content[i + 1] == '\0')
		{
			++element_nb;
		}
	}
	return element_nb;
}

static char** ptr_array_reallocate(char** word_array, int element_nb, int size_added)
{
	char**	new_word_array;
	int		i;

	new_word_array = NULL;
	new_word_array = malloc(sizeof(*new_word_array) * (element_nb + size_added));
	if(element_nb > 0)
	{
		i = -1;
		while(++i < element_nb)
		{
			new_word_array[i] = word_array[i];
		}
		free(word_array);
		word_array = NULL;
	}
	return new_word_array;
}

static char* extract_str(char* str, int start, int end)
{
	char*	extracted_str;
	int		i;
	int		count;

	count = 0;
	extracted_str = NULL;
	if(start >= 0 && start <= end && end < (int)strlen(str))
	{
		extracted_str = malloc(sizeof(*extracted_str) * (end - start + 2));
		i = start - 1;
		while(++i <= end)
		{
			extracted_str[count++] = str[i];
		}
		extracted_str[count] = '\0';
	}
	return extracted_str;
}


static char* choose_word(char** word_array)
{
	char*	word;
	int		iword;
	int		length;
	int		i;

	word = NULL;
	i = -1;
	length = 0;
	while(word_array[++i] != NULL)
	{
		++length;
	}
	srand(time(NULL));
	iword = rand() % length;
	word = strdup(word_array[iword]);
	return word;
}
