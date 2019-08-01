/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 15:03:42 by snechaev          #+#    #+#             */
/*   Updated: 2019/08/01 14:31:37 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void ft_error(const char *s, int n)
{
	write(1, "ft_ls: ", 7);
	ft_putstr(s);
	write(1, ": ", 2);
	if (n == 1)
		ft_putstr("No such file or directory\n");
}

void print_count_lst(t_list *l)
{
	int i = 0;
	while (l)
	{
		printf("%s\n", (char *)l->content->d_name);
		printf("elem lst = %d ", i);
		l = l->next;
		i++;
	}
	printf("\n");
}

t_list *to_list(t_list *list, struct dirent *f, int count)
{
	t_list *head;
	t_list *current;
	t_list *elem;

	if (count == 0)
	{
		head = ft_lstnew(f, sizeof(struct dirent));
	}
	else
	{
		elem = ft_lstnew(f, sizeof(struct dirent));
		current = list;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = elem;
		head = list;
	}
	return (head);
}

int is_less(void *a, void *b)
{
	if (ft_strcmp((char *)a, (char *)b) < 0)
		return (1);
	else
		return (0);
}

void reading(const char *str)
{
	DIR *dir;
	struct dirent *f;
	t_list *list;
	int count;

	dir = opendir(str);
	f = NULL;
	if (!dir)
		ft_error(str, 1);
	count = 0;
	list = NULL;
	while ((f = readdir(dir)) != NULL)
	{
		printf("%s\n", f->d_name);
		list = to_list(list, f, count);
		count++;
	}
	list = ft_sort_list(list, is_less);
	print_count_lst(list);
}