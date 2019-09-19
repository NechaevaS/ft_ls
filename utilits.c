/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 08:49:02 by snechaev          #+#    #+#             */
/*   Updated: 2019/09/18 16:47:32 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_error(const char *s, int n)
{
	write(1, "ft_ls: ", 7);
	if (n == 1)
	{
		ft_putstr(s);
		write(1, ": ", 2);
		ft_putstr("No such file or directory\n");
		exit(0);
	}
	if (n == 2)
	{
		ft_putstr(" illegal option -- ");
		s++;
		ft_putstr(s);
		write(1, "\n", 1);
		ft_putstr("usage: ft_ls [-ARSacflrtu1] [file ...]\n");
		exit(0);
	}
}

int		count_blocks(t_path *p)
{
	int	n_bl;

	n_bl = 0;
	while (p)
	{
		n_bl = n_bl + (p->stat->st_blocks);
		p = p->next;
	}
	return (n_bl);
}


void	get_max_n(t_path *p, t_help *max)
{
	int		gr_len;
	int 	ow_len;

	while (p)
	{
		gr_len = ft_strlen(getgrgid(p->stat->st_gid)->gr_name);
		ow_len = ft_strlen(getpwuid(p->stat->st_uid)->pw_name);
		if (p->stat->st_nlink > max->max_lnk)
			max->max_lnk = p->stat->st_nlink;
		if (p->stat->st_size >  max->max_size)
			max->max_size = p->stat->st_size;
		if ( gr_len >  max->max_group_name)
			max->max_group_name = gr_len;
		if (ow_len >  max->max_own_name)
			max->max_own_name = ow_len;
		p = p->next;
	}
	max->max_lnk = ft_strlen(ft_itoa(max->max_lnk));
	max->max_size = ft_strlen(ft_itoa(max->max_size));
}

t_path	*path_del(t_path *p)
{
	t_path	*tmp;

	if (!p)
		tmp = NULL;
	else
		tmp = p->next;
	if (p || p->next)
	{
		free(p->name);
		free(p->stat);
		free(p);
		p = NULL;
	}
	return (tmp);
}
