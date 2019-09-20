/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:13:52 by snechaev          #+#    #+#             */
/*   Updated: 2019/09/19 11:15:32 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	path_del(t_path *p)
{
	while (p)
	{
		p = elem_del(p);
	}
}

t_path	*elem_del(t_path *p)
{
	t_path	*tmp;

	if (!p)
		tmp = NULL;
	else
		tmp = p->next;
	if (p || p->next)
	{
		ft_strdel(&(p)->name);
		ft_strdel(&(p)->all_p);
		free(p->stat);
        free(p->max);
		ft_strdel(&(p)->link);
		free(p);
		p = NULL;
	}
	return (tmp);
}

t_help	*init_max()
{
	t_help	*max;

	max = (t_help *)malloc(sizeof(t_help));
	max->max_lnk = 0;
	max->max_size = 0;
	max->max_group_name = 0;
	max->max_own_name = 0;
	return (max);
}