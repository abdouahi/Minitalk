SERVER = server
CLIENT = client

SERVER_SRC = server.c
CLIENT_SRC = client.c
MAN_SRC = ft_atoi.c

FT_PRINTF_SRC = ft_printf/ft_pointer.c ft_printf/ft_printf.c ft_printf/ft_putstr.c \
               ft_printf/ft_putchar.c ft_printf/ft_putnbr.c ft_printf/ft_putnbr_unsigned.c \
               ft_printf/ft_putnbr_hex.c

SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
COMMON_OBJ = $(MAN_SRC:.c=.o)
FT_PRINTF_OBJ = $(FT_PRINTF_SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJ) $(COMMON_OBJ) $(FT_PRINTF_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT): $(CLIENT_OBJ) $(COMMON_OBJ) $(FT_PRINTF_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

ft_printf/%.o: ft_printf/%.c minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ) $(COMMON_OBJ) $(FT_PRINTF_OBJ)

fclean: clean
	rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re