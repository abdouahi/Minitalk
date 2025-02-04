CC = cc
CFLAGS = -Wall -Wextra -Werror

all: server client server_bonus client_bonus

server: server.c
	$(CC) $(CFLAGS) -o $@ $<

client: client.c
	$(CC) $(CFLAGS) -o $@ $<

server_bonus: server_bonus.c
	$(CC) $(CFLAGS) -o $@ $<

client_bonus: client_bonus.c
	$(CC) $(CFLAGS) -o $@ $<

bonus: server_bonus client_bonus

clean:
	rm -f server client server_bonus client_bonus

fclean: clean

re: fclean all

.PHONY: all clean fclean re bonus
