/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info_l2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:18:23 by snechaev          #+#    #+#             */
/*   Updated: 2019/09/20 11:21:52 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_num_lnk(t_path *path)
{
	int		n_lnk;
	char	*s;
	int		ws;

	s = ft_itoa(path->stat->st_nlink);
	n_lnk = ft_strlen(s);
	ws = path->max->max_lnk - n_lnk;
	while (ws > 0)
	{
		ft_putstr(" ");
		ws--;
	}
	ft_putstr(s);
	free(s);
}

void	print_gr_name(t_path *path)
{
	int	ws;
	int	len;

	ft_putstr(getgrgid(path->stat->st_gid)->gr_name);
	len = ft_strlen(getgrgid(path->stat->st_gid)->gr_name);
	ws = path->max->max_group_name - len;
	while (ws > 0)
	{
		ft_putstr(" ");
		ws--;
	}
}

void	print_ow_name(t_path *p)
{
	int	ws;

	ft_putstr(getpwuid(p->stat->st_uid)->pw_name);
	ws = p->max->max_own_name - ft_strlen(getpwuid(p->stat->st_uid)->pw_name);
	while (ws > 0)
	{
		ft_putstr(" ");
		ws--;
	}
}
