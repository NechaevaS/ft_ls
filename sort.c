/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 14:19:47 by snechaev          #+#    #+#             */
/*   Updated: 2019/09/13 16:52:48 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_less_name(t_path *s1, t_path *s2, char c)
{
	char	*c1;
	char	*c2;

	if (!c)
		return (-1);
	c1 = ft_strdup(s1->name);
	c2 = ft_strdup(s2->name);

	if (ft_strcmp(c1, c2) <= 0)
		return (1);
	free(c1);
	free(c2);
	return (0);
}

int		is_less_sise(t_path *s1, t_path *s2, char c)
{

	if (!c)
		return (-1);
	if (s1->stat->st_size >= s2->stat->st_size)
		return (1);
	return (0);
}

t_path *sort_f(t_path *p)
{
	t_path	*head;
	t_path	*tmp;

	head = p;
	while (p->next)
	{
			if (!ft_strcmp(".", p->next->name))
			{
				tmp = p->next;
				p->next = p->next->next;
				tmp->next = head;
				head = tmp;
			}
			if (!ft_strcmp("..", p->next->name))
			{
				tmp = p->next;
				p->next = p->next->next;
				if (!ft_strcmp(".", head->next->name))
				{
					tmp->next = head->next;
					head->next = tmp;
				}
				else
				{
					tmp->next = head;
					head = tmp;
				}
			}
		p = p->next;
	}

	return (head);
}
int		is_less_time(t_path *s1, t_path *s2, char c)
{
	if (c == 'u')
	{
		if (s1->stat->st_atime >= s2->stat->st_atime)
			return (1);
	}
	if (c == 'c')
	{
		if (s1->stat->st_ctime >= s2->stat->st_ctime)
			return (1);
	}
	if (c == 'm')
	{
		if (s1->stat->st_mtime >= s2->stat->st_mtime)
			return (1);
	}
	return (0);
}

t_path	*sort(t_path *p, int (*cmp)(t_path *, t_path *, char), int r, char s)
{
	t_path	*head;
	t_path	*current;

	head = p;
	while (p)
	{
		current = p->next;
		while (current)
		{
			if ((cmp(p, current, s) == 0 && !r) ||
				(cmp(p, current, s) == 1 && r))
			{
				swap_elem(p, current);
			}
			current = current->next;
		}
		p = p->next;
	}
	return (head);
}

t_path	*sort_path(t_path *path, char *flags)
{
	t_path		*res;
	int			r;

	r = 0;
	if (ft_strrchr(flags, 'r'))
		r = 1;
	if (ft_strrchr(flags, 'f'))
		res = sort_f(path);
	else if (ft_strrchr(flags, 'S') != NULL)
	{
		res = sort(path, is_less_sise, r, 'S');
	}
	else if (ft_strrchr(flags, 't') != NULL)
	{
		if (ft_strrchr(flags, 'c') != NULL)
			res = sort(path, is_less_time, r, 'c');
		else if (ft_strrchr(flags, 'u'))
			res = sort(path, is_less_time, r, 'u');
		else
			res = sort(path, is_less_time, r, 'm');
	}
	else
		res = sort(path, is_less_name, r, 'z');
	return (res);
}
