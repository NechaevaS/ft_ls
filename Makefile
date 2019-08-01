# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/07 14:47:44 by snechaev          #+#    #+#              #
#    Updated: 2019/08/01 12:14:27 by snechaev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

OBJS = main.o\
       		read.o\
			flags.o\

CFLAGS = -Wall -Wextra -Werror -g

all : $(NAME)

$(NAME) : $(OBJS) lib
	gcc $(CFLAGS) libft/libft.a $(OBJS) -o $(NAME)

$(OBJS) : ft_ls.h

lib:
	@make -C libft

clean :
	rm -f $(OBJS)
	@make -C libft/ clean

fclean : clean
	rm -f $(NAME)
	@make -C libft/ fclean

re: fclean all
