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

void print_folder_name(t_path *path, char *flags, int r)
{
	if (r)
		ft_putstr("\n");
	if (ft_strrchr(flags, 'R'))
		ft_putstr("./");
	ft_putstr(path->name);
	ft_putstr(":\n");
}

void ft_ls_rec(t_path *path, char *flags, int r)
{
	t_path *n_p;

	if (ft_strcmp(".", path->name))
		print_folder_name(path, flags, r);
	if (!(n_p = create_new_path(path->name, flags)))
		return;
	if (ft_strrchr(flags, 'l'))
	{
		ft_putstr("total ");
		ft_putnbr(count_blocks(n_p));
		ft_putstr("\n");
	}
	print_path(n_p, flags);
	while (n_p && ft_strrchr(flags, 'R'))
	{
		if ((S_ISDIR(n_p->stat->st_mode)) && ft_strcmp(".", n_p->name) && ft_strcmp("..", n_p->name))
		{
			if (!ft_strcmp("/", path->name))
				path->name = ft_strjoin(path->name, n_p->name);
			else
				path->name = ft_strjoin(ft_strjoin(path->name, "/"), n_p->name);
			ft_ls_rec(path, flags, r + 1);
		}
		n_p = n_p->next;
	}
}

void ft_ls(t_path *path, char *flags, int argc)
{
	t_path *tmp;
	int		r;

	r = 0;
	if (!path)
		return;
	tmp = path;
	if (ft_strrchr(flags, 'l') && !argc)
	{
		ft_putstr("total ");
		ft_putnbr(count_blocks(tmp));
		ft_putstr("\n");
	}
	while (tmp)
	{
		if (!S_ISDIR(tmp->stat->st_mode))
 			printing(tmp, flags);
		if (S_ISDIR(tmp->stat->st_mode) && !argc && ft_strcmp(".", tmp->name))
			printing(tmp, flags);
		tmp = tmp->next;
	}
	if (argc || ft_strrchr(flags, 'R'))
	{
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
			tmp = tmp->next;
			r++;
		}
	}

}
