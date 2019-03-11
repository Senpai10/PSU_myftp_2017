##
## EPITECH PROJECT, 2018
## lemipc
## File description:
## Makefile
##

CC	=	gcc

NAME	=	server

CFLAGS	=	-Iinclude -W -Wall -Wextra

SRC	=	src/check_error.c		\
		src/display_message.c		\
		src/create_server.c		\
		src/do_commands.c		\
		src/get_next_line.c		\
		src/working_directory.c		\
		src/authentication.c		\
		src/logout.c			\
		src/help.c			\
		src/data_transfer.c		\
		src/commands_tab.c		\
		src/list.c			\
		src/download.c			\
		src/upload.c

SRC_MAIN=	src/main.c

OBJ	=	$(SRC:.c=.o)		\
		$(SRC_MAIN:.c=.o)

RM		=	rm -f

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME) units

re:	fclean all
