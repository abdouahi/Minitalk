CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a

all: $(LIBFT) client server

$(LIBFT):
	@make -C libft

client: client.c $(LIBFT)
	@$(CC) $(CFLAGS) client.c -Llibft -lft -o client

server: server.c $(LIBFT)
	@$(CC) $(CFLAGS) server.c -Llibft -lft -o server

clean:
	@make -C libft clean

fclean: clean
	@rm -f client server
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
