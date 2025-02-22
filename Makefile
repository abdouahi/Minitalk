NAME = server client
BONUS = server_bonus client_bonus

all: $(NAME)

bonus: $(BONUS)

server:
	cc -Wall -Wextra -Werror server.c -o server

client:
	cc -Wall -Wextra -Werror client.c -o client

server_bonus:
	cc -Wall -Wextra -Werror server_bonus.c -o server_bonus

client_bonus:
	cc -Wall -Wextra -Werror client_bonus.c -o client_bonus

clean:
	rm -f $(NAME) $(BONUS)

fclean: clean

re: fclean all
