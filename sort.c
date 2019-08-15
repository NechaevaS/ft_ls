/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 14:19:47 by snechaev          #+#    #+#             */
/*   Updated: 2019/08/08 16:45:37 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void swap_elem(t_path *p1, t_path *p2)
{
	int     t_type;
	char    *t_name;
	struct stat *t_stat;

	t_type = p1->type;
	p1->type = p2->type;
	p2->type = t_type;
	t_name = p1->name;
	p1->name = p2->name;
	p2->name = t_name;
	t_stat = p1->stat;
	p1->stat = p2->stat;
	p2->stat = t_stat;
}

int is_less_name(t_path *s1, t_path *s2, char c)
{
	char *c1;
	char *c2;

	if (!c)
		return (-1);
	c1 = ft_strdup(s1->name);
	c2 = ft_strdup(s2->name);
	c1[0] = ft_tolower(c1[0]);
	c2[0] = ft_tolower(c2[0]);
	if (ft_strcmp(c1, c2) <= 0)
		return (1);
	free(c1);
	free(c2);
	return (0);
}

int is_less_sise(t_path *s1, t_path *s2, char c)
{

	if (!c)
		return (-1);
	if (s1->stat->st_size <= s2->stat->st_size)
		return(1);
	return (0);
}

int is_less_time(t_path *s1, t_path *s2, char c)
{
	if (c == 'u')
	{
		if (s1->stat->st_atime >= s2->stat->st_atime)
		return(1);
	}
	if (c == 'c')
	{
		if (s1->stat->st_ctime >= s2->stat->st_ctime)
		return(1);
	}
	if (c == 'm')
	{
		if (s1->stat->st_mtime >= s2->stat->st_mtime)
		return(1);
	}
	return (0);
}

t_path *sorting(t_path *path, int (*cmp)(t_path *, t_path *, char), int r, char c)
{
	t_path *head;
	t_path *current;

	head = path;
	while (path)
	{
		current = path->next;
		while (current)
		{
			if ((cmp(path, current, c) == 0 && !r) ||
				(cmp(path, current, c) == 1 && r))
			{
				swap_elem(path, current);
			}
			current = current->next;
		}
		path = path->next;
	}
	return (head);
}

t_path          *sort_path(t_path *path, char *flags)
{
	t_path		*res;
	int			r;

	r = 0;
	if (ft_strrchr(flags, 'r'))
		r = 1;
	if (ft_strrchr(flags, 'f'))
		res = path;
	else if (ft_strrchr(flags, 'S') != NULL)
	{
		res = sorting(path, is_less_sise, r, 'S');
	}
	else if (ft_strrchr(flags, 't') != NULL)
	{
		if (ft_strrchr(flags, 'c') != NULL)
			res = sorting(path, is_less_time, r, 'c');
		else if (ft_strrchr(flags, 'u'))
			res = sorting(path, is_less_time, r, 'u');
		else
			res = sorting(path, is_less_time, r, 'm');
	}
	else
		res = sorting(path, is_less_name, r, 'z');
	return (res);
}