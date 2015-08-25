#include "ft_put.h"
#include <unistd.h>
#include <string.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_putstr(char const* str)
{
	int length;

	length = strlen(str);
	write(1, str, length);
}
