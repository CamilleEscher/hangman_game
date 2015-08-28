#ifndef COLOR_H
#define COLOR_H
#include <stdio.h>

typedef enum	e_style
{	
	NORMAL	= 0x0,
	BOLD	= 0x1,
	UL		= 0x2,
	HL		= 0x4
}				t_style;

typedef enum	e_color
{
	BLACK,
	RED,
	BLUE,
	GREEN,
	CYAN,
	YELLOW,
	PINK,
	GRAY,
	NONE
}				t_color;

void print_color_code(int fd, t_style style, t_color background, t_color text);

#endif
