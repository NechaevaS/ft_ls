/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 08:49:02 by snechaev          #+#    #+#             */
/*   Updated: 2019/09/20 16:30:50 by snechaev         ###   ########.fr       */
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

void	fill_max(t_path *p, t_help *tmp)
{
	while (p)
	{
		p->max->max_lnk = tmp->max_lnk;
		p->max->max_size = tmp->max_size;
		p->max->max_group_name = tmp->max_group_name;
		p->max->max_own_name = tmp->max_own_name;
		p = p->next;
	}
}

void	get_max_l_s(t_path *p, t_help *tmp)
{
	char	*lnk;
	char	*size;

	while (p)
	{
		lnk = ft_itoa(p->stat->st_nlink);
		size = ft_itoa(p->stat->st_size);
		if ((int)ft_strlen(lnk) > tmp->max_lnk)
			tmp->max_lnk = ft_strlen(lnk);
		if ((int)ft_strlen(size) > tmp->max_size)
			tmp->max_size = ft_strlen(size);
		p = p->next;
		free(lnk);
		free(size);
	}
}

void	get_max_n(t_path *path)
{
	t_help	*tmp;
	t_path	*p;

	tmp = init_max();
	get_max_l_s(path, tmp);
	p = path;
	while (p)
	{
		if ((int)ft_strlen(getgrgid(p->stat->st_gid)->gr_name)
			> tmp->max_group_name)
			tmp->max_group_name = ft_strlen(getgrgid(p->stat->st_gid)->gr_name);
		if ((int)ft_strlen(getpwuid(p->stat->st_uid)->pw_name)
			> tmp->max_own_name)
			tmp->max_own_name = ft_strlen(getpwuid(p->stat->st_uid)->pw_name);
		p = p->next;
	}
	p = path;
	fill_max(p, tmp);
	free(tmp);
}
