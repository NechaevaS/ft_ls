/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 11:32:01 by snechaev          #+#    #+#             */
/*   Updated: 2019/09/16 12:43:02 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_folder_name(t_path *path, int r, char *flags, t_path *n_p)
{
	if ((ft_strncmp(".", path->name, 1) || (!ft_strncmp("./", path->name, 2)
		&& ft_strrchr(flags, 'R'))))
	{
		if (r > 1)
			ft_putstr("\n");
		if (r)
		{

			ft_putstr(path->name);
			ft_putstr(":\n");
		}
	}
	if (ft_strrchr(flags, 'l'))
	{
		ft_putstr("total ");
		ft_putnbr(count_blocks(n_p));
		ft_putstr("\n");
	}
}

void	ft_ls_rec(t_path *path, char *flags, int *r)
{
	t_path	*n_p;
	char	*tmp;

	if (!(n_p = create_new_path(path->name, flags)))
		return ;
	print_folder_name(path, *r, flags, n_p);
	print_path(n_p, flags, 0, *r);
	tmp = path->name;
	while (n_p && ft_strrchr(flags, 'R'))
	{
		if ((S_ISDIR(n_p->stat->st_mode)) && ft_strcmp(".", n_p->name)
			&& ft_strcmp("..", n_p->name))
		{
			if (!ft_strcmp("/", path->name))
				path->name = ft_strjoin(path->name, n_p->name);
			else
				path->name = ft_strjoin(ft_strjoin(path->name, "/"), n_p->name);
			(*r)++;
			ft_ls_rec(path, flags, r);
			path->name = tmp;
		}
		n_p = path_del(n_p);
	}
}

void	print_argc(t_path *path, char *flags, int argc, int *r)
{

	if (!path)
		return ;
	if (argc && ft_strncmp("../", path->name, 3))
	{
		print_path(path, flags, argc, 0);
		(*r)++;
	}

}

void	ft_ls(t_path *path, char *flags, int argc)
{
	int		r;
	int		f;

	if (!path)
		return ;
	r = 0;
	print_argc(path, flags, argc, &r);
	f = 0;
	while (path)
	{
		if (S_ISDIR(path->stat->st_mode))
		{
			if (f == 0 && !path->next)
				r = 0;
			if (f == 0 && !argc)
				r = 2;
			ft_ls_rec(path, flags, &r);
			f++;
		}
		if (!argc && !S_ISDIR(path->stat->st_mode))
			printing(path, flags, 0, 0);
		path = path->next;
		r++;
	}
}
