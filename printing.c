/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:44:14 by snechaev          #+#    #+#             */
/*   Updated: 2019/09/12 14:49:12 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_name(t_path *path, char *flags)
{
	if (!ft_strrchr(flags, 'f'))
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

void	print_path(t_path *p, char *flags, int argc)
{
	if (!ft_strrchr(flags, '1') && !ft_strrchr(flags, 'l'))
		print_column(p, flags, argc);
	else
	{
		while (p)
		{
			printing(p, flags);
			p = p->next;
		}
		if (!ft_strrchr(flags, 'l'))
			ft_putstr("\n");
	}
}

void	printing_l(t_path *path, char *flags)
{
	print_type(path);
	print_permission(*path);
	if (path->attr)
		ft_putchar(path->attr);
	else
		ft_putstr(" ");
	ft_putstr(" ");
	print_num_lnk(path);
	ft_putstr(" ");
	ft_putstr(getpwuid(path->stat->st_uid)->pw_name);
	ft_putstr("  ");
	ft_putstr(getgrgid(path->stat->st_gid)->gr_name);
	ft_putstr(" ");
	print_size(path);
	ft_putstr(" ");
	print_time(path);
	ft_putstr(" ");
	print_name(path, flags);
	// if (S_ISLNK(path->stat->st_mode))
	// {
		ft_putstr(" -> ");
		ft_putstr(path->link);
//	}
	ft_putstr("\n");
}

void	printing(t_path *path, char *flags)
{

	if (ft_strrchr(flags, 'l'))
	{
		printing_l(path, flags);
	}
	else
	{
		print_name(path, flags);
	}
}
