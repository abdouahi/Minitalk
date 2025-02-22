NAME = server client

all: $(NAME)

server:
	cc -Wall -Wextra -Werror server.c -o server

client:
	cc -Wall -Wextra -Werror client.c -o client

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
