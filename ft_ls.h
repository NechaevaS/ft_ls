/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 14:02:03 by snechaev          #+#    #+#             */
/*   Updated: 2019/08/08 16:16:35 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <stdlib.h>
# include <sys/xattr.h>
#include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include <errno.h>
# include "libft/libft.h"

# define FLAGS		("laARrtT")

typedef struct
{
	int				l;
	int				a;
	int				R;
	int				r;
	int				t;
}					t_flags;

typedef struct 		s_path
{
	// struct stat		*stat;
	int				type;
	char			*name;
	struct s_path	*next;
}					t_path;


void			ft_error(const char *s, int n);
t_path			*add_to_path(t_path *path, char *curr);
// int				is_less(void *a, void *b);
// void 			reading(const char *str);
void			print_path(t_path *path);
#endif