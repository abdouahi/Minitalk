CC = cc
CFLAGS = -Wall -Wextra -Werror

SERVER = server
CLIENT = client
SRV_SRC = server.c
CLI_SRC = client.c

all: $(SERVER) $(CLIENT)

$(SERVER):
	$(CC) $(CFLAGS) $(SRV_SRC) -o $(SERVER)

$(CLIENT):
	$(CC) $(CFLAGS) $(CLI_SRC) -o $(CLIENT)

clean:
	rm -f $(SERVER) $(CLIENT)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
