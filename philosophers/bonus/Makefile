# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/17 13:06:56 by cpollito          #+#    #+#              #
#    Updated: 2022/06/27 19:59:40 by cpollito         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

HEADER = philosophers_bonus.h

SRCS = main_bonus.c routine_bonus.c utils_bonus.c dinner_begins_bonus.c time_bonus.c init_bonus.c 

OBJS = $(SRCS:.c=.o)

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -g 

RM		= rm -rf

.PHONY	:	all clean fclean re bonus

all :  $(NAME)

bonus : all

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o		: %.c $(HEADER)
	$(CC) $(CFLAGS) $(RACE) -c $< -o $@

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME)

re	: fclean all
