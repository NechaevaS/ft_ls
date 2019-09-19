/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:44:14 by snechaev          #+#    #+#             */
/*   Updated: 2019/09/19 10:01:02 by snechaev         ###   ########.fr       */
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
		if (S_ISCHR(path->stat->st_mode))
			ft_putstr(COL_CHR);
		if (path->stat->st_mode & S_IXUSR && S_ISREG(path->stat->st_mode))
			ft_putstr(COL_EXE);
		ft_putstr(path->name);
		ft_putstr(COL_CLR);
	}
	else
		ft_putstr(path->name);
}

void	print_path(t_path *p, char *flags, int argc, int r, t_help	*max)
{
	get_max_n(p, max);
	if (!ft_strrchr(flags, '1') && !ft_strrchr(flags, 'l')
		&& isatty(fileno(stdout)))
		print_column(p, flags, argc, max);
	else
	{
		while (p)
		{
			if (!r)
			{
				if (!S_ISDIR(p->stat->st_mode)
					|| (S_ISDIR(p->stat->st_mode) && !argc))
				{
					printing(p, flags, max);
					ft_putstr("\n");
				}
			}
			else
			{
				printing(p, flags, max);
				ft_putstr("\n");
			}
			p = p->next;
		}
	}
	if (argc && r)
		ft_putstr("\n");
}

void	printing_l(t_path *path, char *flags, t_help *max)
{
	print_type(path);
	print_permission(*path);
	if (path->attr)
		ft_putchar(path->attr);
	else
		ft_putstr(" ");
	ft_putstr(" ");
	print_num_lnk(path, max);
	ft_putstr(" ");
	print_ow_name(path, max);
	ft_putstr("  ");
	print_gr_name(path, max);
	ft_putstr("  ");
	print_size(path, max);
	ft_putstr(" ");
	print_time(path, flags);
	ft_putstr(" ");
	print_name(path);
	if (S_ISLNK(path->stat->st_mode))
	{
		ft_putstr(" -> ");
		ft_putstr(path->link);
	}
}

void	printing(t_path *path, char *flags, t_help	*max)
{
	if (ft_strrchr(flags, 'l'))
	{
		printing_l(path, flags, max);
	}
	else
	{
		print_name(path);
	}
}
