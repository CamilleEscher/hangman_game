#include "color.h"
#include <unistd.h>
#include <stdio.h>

static void print_style_code(t_style style, int fd);

static void print_background_code(t_color background, int fd);

static void print_text_code(t_color text, int fd);

void print_color_code(int fd, t_style style, t_color background, t_color text)
{
	write(fd, "\033[", 2);
	print_style_code(style, fd);
	print_background_code(background, fd);
	print_text_code(text, fd);
}

static void print_style_code(t_style style, int fd)
{	
	if(style & NORMAL)
	{
		write(fd, "0;", 2);	
	}
	if(style & BOLD)
	{
		write(fd, "1;", 2);
	}
	if(style & UL)
	{
		write(fd, "4;", 2);
	}
	if(style & HL)
	{
		write(fd, "7;", 2);
	}
}

static void print_background_code(t_color background, int fd)
{
	switch(background)
	{
		case BLACK :
		    write(fd, "40;", 3); break;	
		case RED :
		    write(fd, "41;", 3); break;	
		case BLUE :
		    write(fd, "44;", 3); break;	
		case GREEN :
		    write(fd, "42;", 3); break;	
		case CYAN :
		    write(fd, "46;", 3); break;	
		case YELLOW :
		    write(fd, "43;", 3); break;	
		case PINK :
		    write(fd, "45;", 3); break;	
		case GRAY :
		    write(fd, "47;", 3); break;	
		case NONE :
		    break;
		default :
			break;
	}
}

static void print_text_code(t_color text, int fd)
{
	switch(text)
	{
		case BLACK :
		    write(fd, "30m", 3); break;	
		case RED :
		    write(fd, "31m", 3); break;	
		case BLUE :
		    write(fd, "34m", 3); break;	
		case GREEN :
		    write(fd, "32m", 3); break;	
		case CYAN :
		    write(fd, "36m", 3); break;	
		case YELLOW :
		    write(fd, "33m", 3); break;	
		case PINK :
		    write(fd, "35m", 3); break;	
		case GRAY :
		    write(fd, "37m", 3); break;	
		case NONE :
		    write(fd, "0m", 2); break;	
		default :
			break;
	}
}
