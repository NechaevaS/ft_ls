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

void swap_elem(void *v1, void *v2)
{
	t_path *p1 = (t_path *)v1;
	t_path *p2 = (t_path *)v2;
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

int is_less_name(void *s1, void *s2, char c)
{
	char *c1;
	char *c2;

	if (!c)
		return (-1);
	c1 = ft_strdup((char *)s1);
	c2 = ft_strdup((char *)s2);
	c1[0] = ft_tolower(c1[0]);
	c2[0] = ft_tolower(c2[0]);
	if (ft_strcmp(c1, c2) <= 0)
		return (1);
	free(c1);
	free(c2);
	return (0);
}

int is_less_sise(void *s1, void *s2, char c)
{
	t_path *c1;
	t_path *c2;

	if (!c)
		return (-1);
	c1 = (t_path *)s1;
	c2 = (t_path *)s2;
		if (c1->stat->st_size <= c2->stat->st_size)
			return(1);
	return (0);
}

int is_less_time(void *s1, void *s2, char c)
{
	t_path *c1;
	t_path *c2;

	c1 = (t_path *)s1;
	c2 = (t_path *)s2;
	if (c == 'u')
	{
		if (c1->stat->st_atime <= c2->stat->st_atime)
		return(1);
	}
	else if (c == 'c')
	{
		if (c1->stat->st_ctime <= c2->stat->st_ctime)
		return(1);
	}
	else if (c == 'm')
	{
		if (c1->stat->st_mtime <= c2->stat->st_mtime)
		return(1);
	}
	return (0);
}

t_path *sorting(t_path *path, int (*cmp)(void *, void *, char), int r, char c)
{
	t_path *head;
	t_path *current;

	head = path;
	while (path)
	{
		current = path->next;
		while (current)
		{
			if ((cmp((void *)(path->name), (void *)(current->name), c) == 0
				&& !r) || (cmp((void *)(path->name), (void *)(current->name), c) == 1
				&& r))
			{
				swap_elem((void *)path, (void *)current);
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
	else if (ft_strrchr(flags, 'f'))
		res = path;
	else if (ft_strrchr(flags, 'S'))
	{
		res = sorting(path, is_less_sise, r, 'S');
			print_path(res);
	}
	else if (ft_strrchr(flags, 't'))
	{
		if (ft_strrchr(flags, 'c'))
			res = sorting(path, is_less_name, r, 'c');
		else if (ft_strrchr(flags, 'u'))
			res = sorting(path, is_less_name, r, 'u');
		else
			res = sorting(path, is_less_name, r, 'm');
	}
	else
		res = sorting(path, is_less_name, r, 'z');
	return (res);
}