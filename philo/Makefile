# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/03 14:54:08 by axbaudri          #+#    #+#              #
#    Updated: 2025/01/13 16:38:45 by axbaudri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[0;31m
GREEN = \033[0;32m
END_COLOR = \033[0m

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

NAME = philo

SRCS = actions.c \
	check_philos.c \
	check_argv.c \
	free_struct.c \
	get_time.c \
	main.c \
	manage_forks.c \
	manage_threads.c \
	philosophers.c \
	string_utils.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
	@echo "$(GREEN)Tout est compile"

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

clean:
	rm -f $(OBJS)
	@echo "$(RED)Tout les fichiers objets sont supprimes$(END_COLOR)"

fclean: clean
	rm -f $(NAME)
	@echo "$(RED)L'executable aussi$(END_COLOR)"

re: fclean all

.PHONY: all clean fclean re
