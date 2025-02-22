CC = cc
CFLAGS = -Wall -Wextra -Werror
SERVER = server
CLIENT = client

all: $(SERVER) $(CLIENT)

$(SERVER):
	$(CC) $(CFLAGS) server.c -o $(SERVER)

$(CLIENT):
	$(CC) $(CFLAGS) client.c -o $(CLIENT)

clean:
	rm -f $(SERVER) $(CLIENT)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
