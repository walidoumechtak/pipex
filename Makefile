CC=cc
CFLAGS=-Wall -Wextra -Werror
NAME=pipex

FOBJ= ft_printf/ft_hexaLower.o \
	ft_printf/ft_hexaUpper.o \
	ft_printf/ft_printf.o \
	ft_printf/ft_printUns.o \
	ft_printf/ft_putchar.o \
	ft_printf/ft_putnbr.o \
	ft_printf/ft_putstr.o \
	ft_printf/ft_vprintf.o \

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
	$(FOBJ) \
	

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
	get_next_line/get_next_line.o \
	get_next_line/get_next_line_utils.o \
	errors/errors.o \
	helped_functions/cmds.o \
	$(FOBJ) \
	
all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bonus: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJ) $(OBJS) 

fclean:
	rm -f $(NAME) $(OBJ) $(OBJS) 

re:fclean all

git:
	git add . && git commit -m "go ..." && git push