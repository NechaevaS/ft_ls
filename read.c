/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 15:03:42 by snechaev          #+#    #+#             */
/*   Updated: 2019/08/08 16:45:14 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_error(const char *s, int n)
{
	write(1, "ft_ls: ", 7);
	ft_putstr(s);
	write(1, ": ", 2);
	if (n == 1)
		ft_putstr("No such file or directory\n");
	if (n == 2)
	{
		ft_putstr("illegal option --");
		ft_putstr(s);
		write(1, "\n", 1);
		ft_putstr("usage: ft_ls [laARrtT] [file ...]\n");
	}
}

int			check_type(char *curr_path)
{
	DIR		*dir;
	int		res;

	res = 0;
	dir = opendir(curr_path);
	if (!dir)
	{
		if (!ft_strcmp("Not a directory", strerror(errno)))
			res = 0;
		else if (!closedir(dir))
			res = 1;
		else
		{
			res = -1;
			ft_error(curr_path, 1);
		}
	}
	return (res);
}

t_path		*add_to_path(t_path *path, char *curr)
{
	t_path	*current;
	t_path	*elem;

	if (!(elem = (t_path *)malloc(sizeof(t_path))))
		return (NULL);

	elem->name = ft_strdup(curr);
	elem->next = NULL;
	//elem->stat = (struct stat *)malloc(sizeof(struct stat));
	elem->type = check_type(curr);
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

