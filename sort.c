/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 14:19:47 by snechaev          #+#    #+#             */
/*   Updated: 2019/09/18 14:17:53 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_less_name(t_path *s1, t_path *s2, char c)
{
	if (!c)
		return (-1);

	if (ft_strcmp(s1->name, s2->name) <= 0)
		return (1);
	return (0);
}

int		is_less_sise(t_path *s1, t_path *s2, char c)
{
	if (!c)
		return (-1);
	if (s1->stat->st_size > s2->stat->st_size)
		return (1);
	if (s1->stat->st_size == s2->stat->st_size
		&& ft_strcmp(s1->name, s2->name) <= 0)
		return (1);
	return (0);
}

int		is_less_time(t_path *s1, t_path *s2, char c)
{
	if (c == 'u')
	{
		if ((s1->stat->st_atime > s2->stat->st_atime))
			// || (s1->stat->st_atime.tv_sec == s2->stat->st_atime.tv_sec
			// && s1->stat->st_atime.tv_nsec > s2->stat->st_atime.tv_nsec)
			// || (s1->stat->st_atime.tv_sec == s2->stat->st_atime.tv_sec
			// && s1->stat->st_atime.tv_nsec == s2->stat->st_atime.tv_nsec
			// && ft_strcmp(s1->name, s2->name) < 0))
			return (1);
	}
	if (c == 'c')
	{
		if ((s1->stat->st_ctime > s2->stat->st_ctime))
			// || (s1->stat->st_ctimespec.tv_sec == s2->stat->st_ctimespec.tv_sec
			// && s1->stat->st_ctimespec.tv_nsec > s2->stat->st_ctimespec.tv_nsec)
			// || (s1->stat->st_ctimespec.tv_sec == s2->stat->st_ctimespec.tv_sec
			// && s1->stat->st_ctimespec.tv_nsec == s2->stat->st_ctimespec.tv_nsec
			// && ft_strcmp(s1->name, s2->name) <= 0))
			return (1);
	}
	if (c == 'm')
	{
		if ((s1->stat->st_mtime > s2->stat->st_mtime))
			// || (s1->stat->st_mtimespec.tv_sec == s2->stat->st_mtimespec.tv_sec
			// && s1->stat->st_mtimespec.tv_nsec > s2->stat->st_mtimespec.tv_nsec)
			// || (s1->stat->st_mtimespec.tv_sec == s2->stat->st_mtimespec.tv_sec
			// && s1->stat->st_mtimespec.tv_nsec == s2->stat->st_mtimespec.tv_nsec
			// && ft_strcmp(s1->name, s2->name) <= 0))
			return (1);
	}
	return (0);
}
// int		is_less_time(t_path *s1, t_path *s2, char c)
// {
// 	if (c == 'u')
// 	{
// 		if ((s1->stat->st_atimespec.tv_sec > s2->stat->st_atimespec.tv_sec)
// 			|| (s1->stat->st_atimespec.tv_sec == s2->stat->st_atimespec.tv_sec
// 			&& s1->stat->st_atimespec.tv_nsec > s2->stat->st_atimespec.tv_nsec)
// 			|| (s1->stat->st_atimespec.tv_sec == s2->stat->st_atimespec.tv_sec
// 			&& s1->stat->st_atimespec.tv_nsec == s2->stat->st_atimespec.tv_nsec
// 			&& ft_strcmp(s1->name, s2->name) < 0))
// 			return (1);
// 	}
// 	if (c == 'c')
// 	{
// 		if ((s1->stat->st_ctimespec.tv_sec > s2->stat->st_ctimespec.tv_sec)
// 			|| (s1->stat->st_ctimespec.tv_sec == s2->stat->st_ctimespec.tv_sec
// 			&& s1->stat->st_ctimespec.tv_nsec > s2->stat->st_ctimespec.tv_nsec)
// 			|| (s1->stat->st_ctimespec.tv_sec == s2->stat->st_ctimespec.tv_sec
// 			&& s1->stat->st_ctimespec.tv_nsec == s2->stat->st_ctimespec.tv_nsec
// 			&& ft_strcmp(s1->name, s2->name) <= 0))
// 			return (1);
// 	}
// 	if (c == 'm')
// 	{
// 		if ((s1->stat->st_mtimespec.tv_sec > s2->stat->st_mtimespec.tv_sec)
// 			|| (s1->stat->st_mtimespec.tv_sec == s2->stat->st_mtimespec.tv_sec
// 			&& s1->stat->st_mtimespec.tv_nsec > s2->stat->st_mtimespec.tv_nsec)
// 			|| (s1->stat->st_mtimespec.tv_sec == s2->stat->st_mtimespec.tv_sec
// 			&& s1->stat->st_mtimespec.tv_nsec == s2->stat->st_mtimespec.tv_nsec
// 			&& ft_strcmp(s1->name, s2->name) <= 0))
// 			return (1);
// 	}
// 	return (0);
// }

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
