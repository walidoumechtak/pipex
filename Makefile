CC=cc
CFLAGS=-Wall -Wextra -Werror
NAME=pipex

OBJ=pipex.o \

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(NAME)

fclean:
	rm -f $(NAME) $(OBJ)

re:fclean all

git:
	git add . && git commit -m "go ..." && git push