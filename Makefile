NAME = philo

SRCS = main.c \
		ft_atoi.c

OBJS = $(addprefix ,$(SRCS:.c=.o))

CC = clang

CFLAGS = -Wall -Wextra -Werror -pthread

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "\033[32m[ ./philo created ]\033[37m"

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re