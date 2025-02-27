NAME = server client

CFLAGS = -Wall -Wextra -Werror -fsanitize=address
LDFLAGS = -fsanitize=address

all: $(NAME)

server:
	cc $(CFLAGS) server.c -o server $(LDFLAGS)

client:
	cc $(CFLAGS) client.c -o client $(LDFLAGS)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
