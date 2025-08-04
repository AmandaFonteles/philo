# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afontele <afontele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/03 20:13:46 by afontele          #+#    #+#              #
#    Updated: 2025/08/04 18:41:30 by afontele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -pthread
INCLUDE = -I.
RM = rm -rf
OBJDIR = obj

SRCS = src/main.c \
	   src/init.c \
	   src/life_cycle.c \
	   src/parse.c \
	   src/monitor.c \
	   src/routine.c \
	   src/actions.c \
	   src/threads.c \
	   src/utils.c

OBJS = $(SRCS:src/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJS) $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
