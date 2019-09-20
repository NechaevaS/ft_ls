/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 08:46:49 by snechaev          #+#    #+#             */
/*   Updated: 2019/09/20 11:54:08 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_path	*sort_f(t_path *p)
{
	t_path	*head;
	t_path	*tmp;

	head = p;
	while (p->next)
	{
		if (!ft_strcmp(".", p->next->name) || !ft_strcmp("..", p->next->name))
		{
			tmp = p->next;
			p->next = p->next->next;
			if (!ft_strcmp("..", p->next->name))
			{
				if (!ft_strcmp(".", head->next->name))
				{
					tmp->next = head->next;
					head->next = tmp;
				}
			}
			tmp->next = head;
			head = tmp;
		}
		p = p->next;
	}
	return (head);
}

void	swap_elem(t_path *p1, t_path *p2)
{
	char			*t_name;
	struct stat		*t_stat;
	char			*t_all_p;
	char			t_attr;
	char			*t_link;

	t_name = p1->name;
	p1->name = p2->name;
	p2->name = t_name;
	t_stat = p1->stat;
	p1->stat = p2->stat;
	p2->stat = t_stat;
	t_all_p = p1->all_p;
	p1->all_p = p2->all_p;
	p2->all_p = t_all_p;
	t_attr = p1->attr;
	p1->attr = p2->attr;
	p2->attr = t_attr;
	t_link = p1->link;
	p1->link = p2->link;
	p2->link = t_link;
}

int		is_less_a_time(t_path *s1, t_path *s2)
{
	if ((s1->stat->st_atimespec.tv_sec > s2->stat->st_atimespec.tv_sec)
		|| (s1->stat->st_atimespec.tv_sec == s2->stat->st_atimespec.tv_sec
		&& s1->stat->st_atimespec.tv_nsec > s2->stat->st_atimespec.tv_nsec)
		|| (s1->stat->st_atimespec.tv_sec == s2->stat->st_atimespec.tv_sec
		&& s1->stat->st_atimespec.tv_nsec == s2->stat->st_atimespec.tv_nsec
		&& ft_strcmp(s1->name, s2->name) < 0))
		return (1);
	return (0);
}

int		is_less_c_time(t_path *s1, t_path *s2)
{
	if ((s1->stat->st_ctimespec.tv_sec > s2->stat->st_ctimespec.tv_sec)
		|| (s1->stat->st_ctimespec.tv_sec == s2->stat->st_ctimespec.tv_sec
		&& s1->stat->st_ctimespec.tv_nsec > s2->stat->st_ctimespec.tv_nsec)
		|| (s1->stat->st_ctimespec.tv_sec == s2->stat->st_ctimespec.tv_sec
		&& s1->stat->st_ctimespec.tv_nsec == s2->stat->st_ctimespec.tv_nsec
		&& ft_strcmp(s1->name, s2->name) <= 0))
		return (1);
	return (0);
}

int		is_less_m_time(t_path *s1, t_path *s2)
{
	if ((s1->stat->st_mtimespec.tv_sec > s2->stat->st_mtimespec.tv_sec)
		|| (s1->stat->st_mtimespec.tv_sec == s2->stat->st_mtimespec.tv_sec
		&& s1->stat->st_mtimespec.tv_nsec > s2->stat->st_mtimespec.tv_nsec)
		|| (s1->stat->st_mtimespec.tv_sec == s2->stat->st_mtimespec.tv_sec
		&& s1->stat->st_mtimespec.tv_nsec == s2->stat->st_mtimespec.tv_nsec
		&& ft_strcmp(s1->name, s2->name) <= 0))
		return (1);
	return (0);
}
