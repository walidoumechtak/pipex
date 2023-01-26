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
	helped_functions/ft_close.o \
	helped_functions/ft_strnstr.o \
	get_next_line/get_next_line.o \
	get_next_line/get_next_line_utils.o \
	errors/errors.o \

OBJS=bonus_part/pipe_bonus.o \
	helped_functions/ft_split.o \
	helped_functions/ft_substr.o \
	helped_functions/free_all.o \
	helped_functions/remove_equal_from_path.o \
	helped_functions/get_cmd_from_input.o \
	helped_functions/path_cmd.o \
	helped_functions/ft_strnstr.o \
	helped_functions/fd_put_string.o \
	helped_functions/ft_close.o \
	helped_functions/ft_strcmp.o \
	helped_functions/cmds.o \
	get_next_line/get_next_line.o \
	get_next_line/get_next_line_utils.o \
	errors/errors.o \

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) ft_printf/libftprintf.a -o $(NAME)

bonus: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) ft_printf/libftprintf.a -o $(NAME)

clean:
	rm -f $(OBJ) $(OBJS)

fclean:
	rm -f $(NAME) $(OBJ) $(OBJS)

re:fclean all

git:
	git add . && git commit -m "go ..." && git push