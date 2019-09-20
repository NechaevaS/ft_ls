/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 11:32:01 by snechaev          #+#    #+#             */
/*   Updated: 2019/09/20 14:18:22 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_folder_name(t_path *path, int r, char *flags, t_path *n_p)
{
	if (ft_strncmp(".", path->name, 1) || ((!ft_strncmp("./", path->name, 2)
		|| !ft_strncmp("../", path->name, 3))
		&& ft_strrchr(flags, 'R')))
	{
		if (r > 1)
			ft_putstr("\n");
		if (r)
		{
			ft_putstr(path->all_p);
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
	t_path	*p;

	if (!(n_p = create_new_path(path->all_p, flags)))
		return ;
	print_folder_name(path, *r, flags, n_p);
	print_path(n_p, flags, 0, r);
	(*r)++;
	tmp = path->name;
	p = n_p;
	while (p && ft_strrchr(flags, 'R'))
	{
		if ((S_ISDIR(p->stat->st_mode)) && ft_strcmp(".", p->name)
			&& ft_strcmp("..", p->name))
		{
			(*r) = 2;
			ft_ls_rec(p, flags, r);
			path->name = tmp;
		}
		p = p->next;
	}
	path_del(n_p);
}

void	print_argc(t_path *path, char *flags, int argc, int *r)
{
	if (!path)
		return ;
	if (argc && ft_strncmp("../", path->name, 3))
	{
		print_path(path, flags, argc, r);
	}
//	(*r)++;
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
			if (f == 0 && !path->next && !r)
				r = 0;
			if (f == 0 && !argc)
				r = 2;
			// else
			// 	r = 1;
			ft_ls_rec(path, flags, &r);
			f++;
		}
		if (!argc && !S_ISDIR(path->stat->st_mode))
			printing(path, flags);
		path = elem_del(path);
		r++;
	}
}
