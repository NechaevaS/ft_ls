/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 15:03:42 by snechaev          #+#    #+#             */
/*   Updated: 2019/09/20 11:33:31 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	add_link_and_attr(t_path *elem)
{
	ssize_t	buflen;

	buflen = listxattr(elem->all_p, NULL, 0, XATTR_NOFOLLOW);
	if (buflen > 0)
		elem->attr = '@';
	else
		elem->attr = 0;
	if (S_ISLNK(elem->stat->st_mode))
		readlink(elem->all_p, elem->link, 1000);
}

t_path	*init_elem(char *curr)
{
	t_path	*elem;

	if (!(elem = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	elem->link = (char *)malloc(1000);
	ft_bzero((char *)elem->link, 1000);
	elem->name = ft_strdup(curr);
	elem->next = NULL;
	elem->stat = (struct stat *)malloc(sizeof(struct stat));
	elem->max = init_max();
	return (elem);
}

void	add_all_p(char *old_p, t_path *elem)
{
	char	*tmp1;
	if (old_p)
	{
		tmp1 = ft_strjoin(old_p, "/");
		elem->all_p = ft_strjoin(tmp1, elem->name);
		ft_strdel(&tmp1);
	}
	else
	{
		if (!ft_strcmp(".", elem->name))
			elem->all_p = "./";
		elem->all_p = ft_strdup(elem->name);
	}
}

t_path	*add_to_path(char *old_p, t_path *path, char *curr)
{
	t_path	*current;
	t_path	*elem;

	elem = init_elem(curr);
	add_all_p(old_p, elem);
	if (lstat(elem->all_p, elem->stat) < 0)
		ft_error(elem->all_p, 1);
	add_link_and_attr(elem);
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
	new_path = sort_path(new_path, flags);
	closedir(dir);
	free(f);
	return (new_path);
}
