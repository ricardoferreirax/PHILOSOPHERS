NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

INCLUDE = includes

SRCS = \
	srcs/actions.c \
	srcs/check_dead.c \
	srcs/init_simulation.c \
	srcs/parsing.c \
	srcs/philo_utils.c \
	srcs/libft_utils.c \
	srcs/philo.c \

OBJS = $(SRCS:.c=.o)

RED = \033[1;37;41m
GREEN = \033[1;30;42m
OFF = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
	@echo -e "$(GREEN) ./philo created! $(OFF)"

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@echo -e "$(RED) Object Files Cleaned! $(OFF)"

fclean: clean
	$(RM) $(NAME)
	@echo -e "$(GREEN) All Cleaned! $(OFF)" 

re: fclean $(NAME)

.PHONY: all clean fclean re