CC = cc
FLAGS = -Wall -Wextra -Werror
NAME = libftft_printf.a
RM = rm -f
AR = ar rcs

SRCS = ft_pointer.c ft_printf.c ft_putstr.c ft_putchar.c ft_putnbr.c ft_putnbr_unsigned.c ft_putnbr_hex.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c ft_printf.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean
