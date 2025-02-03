NAME		= server client
BONUS		= server_bonus client_bonus

SRC_DIR		= src
INC_DIR		= includes
LIBFT_DIR	= libft

SRC			= client.c server.c
BONUS_SRC	= client_bonus.c server_bonus.c

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LIBFT		= $(LIBFT_DIR)/libft.a

all:		$(NAME)

$(LIBFT):
			@make -C $(LIBFT_DIR)

server:		$(SRC_DIR)/server.o $(LIBFT)
			$(CC) $(CFLAGS) $< $(LIBFT) -o $@

client:		$(SRC_DIR)/client.o $(LIBFT)
			$(CC) $(CFLAGS) $< $(LIBFT) -o $@

bonus:		$(BONUS)

server_bonus:	$(SRC_DIR)/server_bonus.o $(LIBFT)
			$(CC) $(CFLAGS) $< $(LIBFT) -o $@

client_bonus:	$(SRC_DIR)/client_bonus.o $(LIBFT)
			$(CC) $(CFLAGS) $< $(LIBFT) -o $@

%.o:		$(SRC_DIR)/%.c
			$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
			rm -f $(SRC_DIR)/*.o
			@make -C $(LIBFT_DIR) clean

fclean:		clean
			rm -f $(NAME) $(BONUS)
			@make -C $(LIBFT_DIR) fclean

re:			fclean all

.PHONY:		all clean fclean re bonus
