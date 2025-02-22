CC = cc
CFLAGS = -Wall -Wextra -Werror
SERVER = server
CLIENT = client

all: $(SERVER) $(CLIENT)

$(SERVER): server.c
	$(CC) $(CFLAGS) $^ -o $@

$(CLIENT): client.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(SERVER) $(CLIENT)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
