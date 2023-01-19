CC=cc
CFLAGS=-Wall -Wextra -Werror
NAME=pipex

OBJ=pipex.o \
	helped_functions/ft_split.o \
	helped_functions/ft_strdup.o \
	helped_functions/ft_strjoin.o \
	helped_functions/ft_strlen.o \
	helped_functions/ft_substr.o \


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