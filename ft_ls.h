/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 14:02:03 by snechaev          #+#    #+#             */
/*   Updated: 2019/08/01 14:25:25 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <stdlib.h>
# include <sys/xattr.h>
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include "libft/libft.h"

typedef struct
{
	int			l;
	int			a;
	int			R;
	int			r;
	int			t;
}				t_flags;


void			ft_error(const char *s, int n);
t_list			*to_list(t_list *list, struct dirent *f, int count);
int				is_less(void *a, void *b);
void 			reading(const char *str);
t_flags			*init_flags();

#endif