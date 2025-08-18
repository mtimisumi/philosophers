# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/10 13:01:11 by mmisumi           #+#    #+#              #
#    Updated: 2025/08/10 14:58:41 by mmisumi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

SRCS := $(shell find src -name "*.c")

OBJS := $(patsubst src/%.c, obj/%.o, $(SRCS))

CC := cc

CFLAGS := -Wall -Werror -Wextra -I. -g

RM := rm -rf

all: obj $(NAME)

obj:
	mkdir -p obj

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

obj/%.o: src/%.c
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJS)
	$(RM) obj

fclean: clean 
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
