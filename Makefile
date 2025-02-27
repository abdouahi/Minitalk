
SERVER = server
CLIENT = client

SERVER_SRC = server.c
CLIENT_SRC = client.c
COMMON_SRC = ft_atoi.c ft_strdup.c


SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
COMMON_OBJ = $(COMMON_SRC:.c=.o)


CC = cc
CFLAGS = -Wall -Wextra -Werror
FSANITIZE = -fsanitize=address


all: $(SERVER) $(CLIENT)


$(SERVER): $(SERVER_OBJ) $(COMMON_OBJ)
	$(CC) $(CFLAGS) $(FSANITIZE) -o $@ $^


$(CLIENT): $(CLIENT_OBJ) $(COMMON_OBJ)
	$(CC) $(CFLAGS) $(FSANITIZE) -o $@ $^


%.o: %.c minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ) $(COMMON_OBJ)


fclean: clean
	rm -f $(SERVER) $(CLIENT)

re: fclean all

debug: CFLAGS += -g
debug: all

.PHONY: all clean fclean re debug