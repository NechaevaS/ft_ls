/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 15:03:42 by snechaev          #+#    #+#             */
/*   Updated: 2019/09/12 15:31:09 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	add_link_and_attr(t_path *elem)
{
	ssize_t	buflen;
//	acl_t	acl;
#ifdef __APPLE__
	buflen = listxattr(elem->all_p, NULL, 0, XATTR_NOFOLLOW);
#else
	buflen = listxattr(elem->all_p, NULL, 0);
#endif
//	acl = acl_get_link_np(elem->all_p, ACL_TYPE_EXTENDED);
	if (buflen > 0)
		elem->attr = '@';
//	else if (acl)
//		elem->attr = '+';
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
	elem->all_p = (char *)malloc(1000);
	ft_bzero((char *)elem->all_p, 1000);
	elem->name = ft_strdup(curr);
	elem->next = NULL;
	elem->stat = (struct stat *)malloc(sizeof(struct stat));
	return (elem);
}

t_path	*add_to_path(char *old_p, t_path *path, char *curr)
{
	t_path	*current;
	t_path	*elem;

	elem = init_elem(curr);
	if (old_p)
		elem->all_p = ft_strjoin(ft_strjoin(old_p, "/"), elem->name);
	else
	{
		if (!ft_strcmp(".", elem->name))
			elem->all_p = "./";
		elem->all_p = elem->name;
	}
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
	if (!ft_strrchr(flags, 'f'))
		new_path = sort_path(new_path, flags);
	return (new_path);
}
