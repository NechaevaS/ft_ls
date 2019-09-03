/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 11:32:01 by snechaev          #+#    #+#             */
/*   Updated: 2019/08/26 18:35:54 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void print_folder_name(t_path *path, int r)
{
	if (r)
		ft_putstr("\n");
	ft_putstr(path->name);
	ft_putstr(":\n");
}

void ft_ls_rec(t_path *path, char *flags, int r)
{
	t_path *n_p;
	char *tmp;

	if ((ft_strcmp(".", path->name) || !ft_strcmp(".", path->name)) &&
		ft_strrchr(flags, 'R') && r)
		print_folder_name(path, r);
	if (!(n_p = create_new_path(path->name, flags)))
		return;
	if (ft_strrchr(flags, 'l'))
	{
		ft_putstr("total ");
		ft_putnbr(count_blocks(n_p));
		ft_putstr("\n");
	}
	print_path(n_p, flags);
	tmp = path->name;
	while (n_p && ft_strrchr(flags, 'R'))
	{
		if ((S_ISDIR(n_p->stat->st_mode)) && ft_strcmp(".", n_p->name) && ft_strcmp("..", n_p->name))
		{
			if (!ft_strcmp("/", path->name))
				path->name = ft_strjoin(path->name, n_p->name);
			else
				path->name = ft_strjoin(ft_strjoin(path->name, "/"), n_p->name);

			ft_ls_rec(path, flags, r + 1);
			path->name = tmp;
		}
		n_p = path_del(n_p);
	}
}

void ft_ls(t_path *path, char *flags,int argc)
{
	t_path *tmp;
	int r;

	r = 0;
	if (!path)
		return;
	tmp = path;
	if (argc)
	{
		while (tmp)
		{
			if (!S_ISDIR(tmp->stat->st_mode))
			{
				printing(tmp, flags);
			}
			tmp = tmp->next;
		}
		r++;
	}
	tmp = path;
	while (tmp)
	{
		if (S_ISDIR(tmp->stat->st_mode))
		{
			if (r == 0)
				ft_ls_rec(tmp, flags, 0);
			else
				ft_ls_rec(tmp, flags, 1);
		}
		else
		{
			if (!argc)
			printing(tmp, flags);
		}
		tmp = tmp->next;
		r++;
	}
}
