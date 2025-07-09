# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/06 21:32:57 by faikhan           #+#    #+#              #
#    Updated: 2025/07/09 00:48:33 by faikhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
SRCS	=	error.c main.c philo_atoi.c philo_utils.c init.c \
			routine.c simulation.c arbitrator.c
OBJS	=	$(SRCS:.c=.o)
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -g -pthread
RM		=	rm -f

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean	:	
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re