/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 15:03:42 by snechaev          #+#    #+#             */
/*   Updated: 2019/08/21 13:19:32 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_path	*add_to_path(t_path *path, char *curr)
{
	t_path	*current;
	t_path	*elem;

	if (!(elem = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	elem->name = ft_strdup(curr);
	elem->next = NULL;
	elem->stat = (struct stat *)malloc(sizeof(struct stat));
	stat(elem->name, elem->stat);
	if (!path)
		return (elem);
	current = path;
	while (current->next)
	{
		current = current->next;
	}
	current->next = elem;
	return (path);
}


