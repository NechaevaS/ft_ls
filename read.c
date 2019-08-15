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
	elem->stat = (struct stat *)malloc(sizeof(struct stat));
	stat(elem->name, elem->stat);
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
// void reading(t_path path, char *flags)
// {
// 	DIR *dir;
// 	struct dirent *f;
// 	t_file *file;
// 	int count;
// 	if (!(file = (t_file *)malloc(sizeof(t_file))))
// 		return (NULL);

// 	dir = opendir(str);
// 	f = NULL;
// 	if (!dir)
// 		ft_error(str, 1);
// 	count = 0;
// 	list = NULL;
// 	while ((f = readdir(dir)) != NULL)
// 	elem->name = ft_strdup(curr);
// 	elem->next = NULL;
// 	//elem->stat = (struct stat *)malloc(sizeof(struct stat));
// 	elem->type = check_type(curr);
// 	if (!path)
// 		return (elem);
// 	current = path;
// 	while (current->next)
// 	{
// 		printf("%s\n", f->d_name);
// 		list = to_list(list, f, count);
// 		count++;
// 		current = current->next;
// 	}
// 	list = ft_sort_list(list, is_less);
// 	print_count_lst(list);
// } 
// 	current->next = elem;
// 	return (path);
// }
