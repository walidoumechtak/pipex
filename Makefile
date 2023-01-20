CC=cc
CFLAGS=-Wall -Wextra -Werror
NAME=pipex

OBJ=pipex.o \
	helped_functions/ft_split.o \
	helped_functions/ft_substr.o \
	helped_functions/free_all.o \
	helped_functions/remove_equal_from_path.o \
	helped_functions/get_cmd_from_input.o \
	helped_functions/path_cmd.o \
	get_next_line/get_next_line.o \
	get_next_line/get_next_line_utils.o \


all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -fsanitize=address

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME) $(OBJ)

re:fclean all

git:
	git add . && git commit -m "go ..." && git push