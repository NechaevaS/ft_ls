/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 15:03:42 by snechaev          #+#    #+#             */
/*   Updated: 2019/08/26 16:18:39 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_path	*add_to_path(char *old_p,t_path *path, char *curr)
{
	t_path	*current;
	t_path	*elem;
	char *name = 0;

	if (!(elem = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	elem->name = ft_strdup(curr);
	elem->next = NULL;
	elem->stat = (struct stat *)malloc(sizeof(struct stat));
	if (old_p)
		name = ft_strjoin(ft_strjoin(old_p, "/"), elem->name);
	else
	{
		if (!ft_strcmp(".", elem->name))
			name = "./";
		name = elem->name;
	}
	stat(name, elem->stat);
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

t_path	*create_new_path(char *path, char *flags)
{
	DIR				*dir;
	struct dirent	*f;
	t_path			*new_path;

	new_path = NULL;
	dir = opendir(path);
	if (!dir)
	{
		ft_error(path, 1);
		return (NULL);
	}
	while ((f = readdir(dir)) != NULL)
	{
		if (f->d_name[0] == '.' && !ft_strrchr(flags, 'f')
			&& !ft_strrchr(flags, 'a') && !ft_strrchr(flags, 'A'))
			continue;
		if ((!ft_strcmp(".", f->d_name) || !ft_strcmp("..", f->d_name))
			&& !ft_strrchr(flags, 'a') && !ft_strrchr(flags, 'f'))
			continue;
		new_path = add_to_path(path, new_path, f->d_name);
	}
	if (!ft_strrchr(flags, 'f'))
		new_path = sort_path(new_path, flags);
	return (new_path);
}
