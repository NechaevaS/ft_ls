/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 12:00:21 by snechaev          #+#    #+#             */
/*   Updated: 2019/08/21 17:05:22 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	swap_elem(t_path *p1, t_path *p2)
{
	char		*t_name;
	struct stat *t_stat;

	t_name = p1->name;
	p1->name = p2->name;
	p2->name = t_name;
	t_stat = p1->stat;
	p1->stat = p2->stat;
	p2->stat = t_stat;
}

