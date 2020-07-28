##
## EPITECH PROJECT, 2018
## / Tek1_PSU_42sh_2018
## File description:
## / Makefile
##

SRC	=	main.c \
		src/*.c

NAME	=	navy

all:	$(NAME)

$(NAME):
	   gcc $(SRC) -o $(NAME)

error:
	   gcc $(SRC) -o $(NAME) -Wall -Wextra

clean:
	   rm -f $(OBJ)

fclean:    clean
	   rm -f $(NAME)

re:	fclean all
