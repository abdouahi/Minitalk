CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
BONUS = client_bonus server_bonus

all: $(LIBFT) client server

bonus: $(LIBFT) $(BONUS)

$(LIBFT):
	@make -C libft

client server: %: %.c $(LIBFT)
	@$(CC) $(CFLAGS) $< -Llibft -lft -o $@

client_bonus server_bonus: %_bonus: %_bonus.c $(LIBFT)
	@$(CC) $(CFLAGS) $< -Llibft -lft -o $@

clean:
	@make -C libft clean

fclean: clean
	@rm -f client server client_bonus server_bonus
	@make -C libft fclean

re: fclean all

.PHONY: all bonus clean fclean re
