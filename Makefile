SERVER = server
CLIENT = client

SERVER_SRC = server.c
CLIENT_SRC = client.c
COMMON_SRC = ft_atoi.c

SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
COMMON_OBJ = $(COMMON_SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

FT_PRINTF_PATH = ./ft_printf
FT_PRINTF = $(FT_PRINTF_PATH)/libftft_printf.a

all: $(FT_PRINTF) $(SERVER) $(CLIENT)

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_PATH)

$(SERVER): $(SERVER_OBJ) $(COMMON_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(FT_PRINTF)

$(CLIENT): $(CLIENT_OBJ) $(COMMON_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(FT_PRINTF)

%.o: %.c minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(FT_PRINTF_PATH) clean
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ) $(COMMON_OBJ)

fclean: clean
	$(MAKE) -C $(FT_PRINTF_PATH) fclean
	rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re