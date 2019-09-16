/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:44:14 by snechaev          #+#    #+#             */
/*   Updated: 2019/09/16 13:00:51 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_name(t_path *path)
{
	if (isatty(fileno(stdout)))
	{
		if (S_ISDIR(path->stat->st_mode))
			ft_putstr(COL_DIR);
		if (S_ISLNK(path->stat->st_mode))
			ft_putstr(COL_LNK);
		if (S_ISREG(path->stat->st_mode))
			ft_putstr(COL_REG);
		if (S_ISBLK(path->stat->st_mode))
			ft_putstr(COL_BLK);
		if (path->stat->st_mode & S_IXUSR && S_ISREG(path->stat->st_mode))
			ft_putstr(COL_EXE);
		ft_putstr(path->name);
		ft_putstr(COL_CLR);
	}
	else
		ft_putstr(path->name);
}

void	print_path(t_path *p, char *flags, int argc, int r)
{
	t_help	max;

	max.max_lnk = get_max_n(p, 1);
	max.max_size = get_max_n(p, 2);
	if (!ft_strrchr(flags, '1') && !ft_strrchr(flags, 'l')
		&& isatty(fileno(stdout)))
		print_column(p, flags, argc);
	while (p)
	{
		if (!r)
		{
			if (!S_ISDIR(p->stat->st_mode)
				|| (S_ISDIR(p->stat->st_mode) && !argc))
			{
				printing(p, flags, max.max_lnk, max.max_size);
				ft_putstr("\n");
			}
		}
		else
		{
			printing(p, flags, max.max_lnk, max.max_size);
			ft_putstr("\n");
		}
		p = p->next;
	}
}

void	printing_l(t_path *path, int max_lnk, int max_size)
{
	print_type(path);
	print_permission(*path);
	if (path->attr)
		ft_putchar(path->attr);
	else
		ft_putstr(" ");
	ft_putstr(" ");
	print_num_lnk(path, max_lnk);
	ft_putstr(" ");
	ft_putstr(getpwuid(path->stat->st_uid)->pw_name);
	ft_putstr("  ");
	ft_putstr(getgrgid(path->stat->st_gid)->gr_name);
	ft_putstr("  ");
	print_size(path, max_size);
	ft_putstr(" ");
	print_time(path);
	ft_putstr(" ");
	print_name(path);
	if (S_ISLNK(path->stat->st_mode))
	{
		ft_putstr(" -> ");
		ft_putstr(path->link);
	}
}

void	printing(t_path *path, char *flags, int max_lnk, int max_size)
{

	if (ft_strrchr(flags, 'l'))
	{
		printing_l(path, max_lnk, max_size);
	}
	else
	{
		print_name(path);
	}
}
