# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/07 14:47:44 by snechaev          #+#    #+#              #
#    Updated: 2019/09/23 15:20:11 by snechaev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

OBJS = main.o\
       		create_new_p.o\
			utilits.o\
			path_utils.o\
			sort.o\
			print_info_l.o\
			print_info_l2.o\
			printing.o\
			ft_ls.o\
			print_column.o\
			sort_utils.o\
			libft/libft.a

CFLAGS = -Wall -Wextra -Werror -g -O0 
#-fsanitize=address

all : $(NAME)

$(NAME) : $(OBJS) lib
	gcc -o $(NAME) $(CFLAGS) $(OBJS)

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
