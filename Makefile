CC = gcc
OPTIONS = -Wall -Werror -Wextra
NAME = hangman
OBJ = main.o color.o game.o ft_put.o user_input.o game_display.o word_list_process.o

all : $(NAME)

$(NAME)	: $(OBJ)
	$(CC) $(OPTIONS) $(OBJ) -o $(NAME)

main.o : main.c
	$(CC) $(OPTIONS) -c main.c

ft_put.o : ft_put.c ft_put.h
	$(CC) $(OPTIONS) -c ft_put.c

game.o : game.c game.h
	$(CC) $(OPTIONS) -c game.c 

color.o : color.c color.h
	$(CC) $(OPTIONS) -c color.c

user_input.o : user_input.c user_input.h
	$(CC) $(OPTIONS) -c user_input.c

game_display.o : game_display.c game_display.h
	$(CC) $(OPTIONS) -c game_display.c

word_list_process.o : word_list_process.c word_list_process.h
	$(CC) $(OPTIONS) -c word_list_process.c

re : fclean $(NAME)

fclean : clean
	rm -f ./hangman

clean : 
	rm -f *.o
