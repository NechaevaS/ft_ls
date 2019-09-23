/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:44:14 by snechaev          #+#    #+#             */
/*   Updated: 2019/09/23 14:29:25 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_name(t_path *path)
{
	if (S_ISDIR(path->stat->st_mode))
		ft_putstr(COL_DIR);
	if (S_ISCHR(path->stat->st_mode))
		ft_putstr(COL_CHR);
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

void	print_path(t_path *p, char *flags, int argc, int *r)
{
	get_max_n(p);
	if (!ft_strrchr(flags, '1') && !ft_strrchr(flags, 'l'))
		print_column(p, argc, r);
	else
	{
		while (p)
		{
			if (!(*r))
			{
				if (!S_ISDIR(p->stat->st_mode)
				|| (S_ISDIR(p->stat->st_mode) && !argc))
					printing(p, flags);
			}
			else
				printing(p, flags);
			p = p->next;
		}
		(*r)++;
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
	print_ow_name(path);
	ft_putstr("  ");
	print_gr_name(path);
	ft_putstr("  ");
	print_size(path);
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

void	printing(t_path *path, char *flags)
{
	if (ft_strrchr(flags, 'l'))
	{
		printing_l(path, flags);
	}
	else
	{
		print_name(path);
	}
	ft_putstr("\n");
}
