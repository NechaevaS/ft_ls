/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 11:32:01 by snechaev          #+#    #+#             */
/*   Updated: 2019/08/23 19:28:06 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_folder_name(char *name)
{
	ft_putstr("./");
	ft_putstr(name);
	ft_putstr(":\n");
}

void	ft_ls_rec(t_path *path, char *flags)
{
	t_path		*n_p;

	print_folder_name(path->name);
	n_p = create_new_path(path, flags);
	if (!n_p)
		return ;
	print_path(n_p);
	while (n_p && ft_strrchr(flags, 'R'))
	{
		if ((S_ISDIR(n_p->stat->st_mode) || S_ISLNK(n_p->stat->st_mode))
			&& ft_strcmp(".", n_p->name) && ft_strcmp("..", n_p->name))
		{
			if (!ft_strcmp("/", path->name))
			{
				path->name = ft_strjoin(path->name, n_p->name);
				ft_ls_rec(path, flags);
			}
			else
			{
				path->name = ft_strjoin(ft_strjoin(path->name, "/"), n_p->name);
				ft_ls_rec(path, flags);
			}
		}
		n_p = n_p->next;
	}
}

void	ft_ls(t_path *path, char *flags)
{
	t_path		*tmp;

	tmp = create_new_path(path, flags);
	if (tmp)
		print_path(tmp);
	while (tmp)
	{
		if (S_ISDIR(tmp->stat->st_mode))
		{
			ft_ls_rec(tmp, flags);
		}
		tmp = tmp->next;
	}
	return ;
}
