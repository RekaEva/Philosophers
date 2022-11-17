# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/17 13:06:56 by cpollito          #+#    #+#              #
#    Updated: 2022/06/28 16:33:02 by cpollito         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

HEADER = philosophers.h

SRCS = main.c routine.c utils.c dinner_begins.c time.c init.c monitoring.c

OBJS = $(SRCS:.c=.o)

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -g 
RACE = -fsanitize=thread

RM		= rm -rf

.PHONY	:	all clean fclean re

all :  $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(RACE) $(OBJS) -o $(NAME)

%.o		: %.c $(HEADER)
	$(CC) $(CFLAGS) $(RACE) -c $< -o $@ 

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME)

re	: fclean all