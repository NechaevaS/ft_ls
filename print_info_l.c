/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info_l.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:44:14 by snechaev          #+#    #+#             */
/*   Updated: 2019/09/18 17:02:18 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_type(t_path *path)
{
	if (S_ISDIR(path->stat->st_mode))
		ft_putchar('d');
	if (S_ISBLK(path->stat->st_mode))
		ft_putchar('b');
	if (S_ISLNK(path->stat->st_mode))
		ft_putchar('l');
	if (S_ISCHR(path->stat->st_mode))
		ft_putchar('c');
	if (S_ISREG(path->stat->st_mode))
		ft_putchar('-');
	if (S_ISFIFO(path->stat->st_mode))
		ft_putchar('p');
	if (S_ISSOCK(path->stat->st_mode))
		ft_putchar('s');
}

void	print_permission(t_path path)
{
	char	res[10];

	ft_memset(res, '-', 9);
	res[9] = '\0';
	if (path.stat->st_mode & S_IRUSR)
		res[0] = 'r';
	if (path.stat->st_mode & S_IWUSR)
		res[1] = 'w';
	if (path.stat->st_mode & S_IXUSR)
		res[2] = 'x';
	if (path.stat->st_mode & S_IRGRP)
		res[3] = 'r';
	if (path.stat->st_mode & S_IWGRP)
		res[4] = 'w';
	if (path.stat->st_mode & S_IXGRP)
		res[5] = 'x';
	if (path.stat->st_mode & S_IROTH)
		res[6] = 'r';
	if (path.stat->st_mode & S_IWOTH)
		res[7] = 'w';
	if (path.stat->st_mode & S_IXOTH)
		res[8] = 'x';
	ft_putstr(res);
}

char *choose_time(t_path *path, char *flags)
{
	char	*t;

	if (ft_strrchr(flags, 'u') && ft_strrchr(flags, 't'))
		t = ctime(&path->stat->st_atime);
	else if (ft_strrchr(flags, 'c') && ft_strrchr(flags, 't'))
		t = ctime(&path->stat->st_ctime);
	else
		t = ctime(&path->stat->st_mtime);
	return (t);
}

void	print_time(t_path *path, char *flags)
{
	char	*t;
	char	**arr;
	time_t	t_now;

	t_now = time(NULL);
	t = choose_time(path, flags);
	arr = ft_strsplit(t, ' ');
	arr[3][5] = '\0';
	arr[4][4] = '\0';
	ft_putstr(arr[1]);
	if (ft_strlen(arr[2]) > 1)
		ft_putchar(' ');
	else
		ft_putstr("  ");
	ft_putstr(arr[2]);
	if (difftime(t_now, path->stat->st_mtime) <= SIX_MONTHS)
	{
		ft_putchar(' ');
		ft_putstr(arr[3]);
	}
	else
	{
		ft_putstr("  ");
		ft_putstr(arr[4]);
	}
}

void	print_size(t_path *path, t_help *max)
{
	char	*s;
	int		len;

	s = ft_itoa(path->stat->st_size);
	len = ft_strlen(s);
	while (max->max_size != len)
	{
		ft_putstr(" ");
		max->max_size--;
	}
	ft_putstr(s);
}

void	print_num_lnk(t_path *path, t_help *max)
{
	int		n_lnk;
	char	*s;

	n_lnk = path->stat->st_nlink;
	s = ft_itoa(n_lnk);
	while (max->max_lnk > (int)ft_strlen(s))
	{
		ft_putstr(" ");
		max->max_lnk--;
	}
	ft_putstr(s);
}

void print_gr_name(t_path *path, t_help *max)
{
	int ws;

	ft_putstr(getgrgid(path->stat->st_gid)->gr_name);
	ws = max->max_group_name - ft_strlen(getgrgid(path->stat->st_gid)->gr_name);
	while (ws > 0)
	{
		ft_putstr(" ");
		ws--;
	}
}
void print_ow_name(t_path *path, t_help *max)
{
	int ws;

	ft_putstr(getpwuid(path->stat->st_uid)->pw_name);
	ws = max->max_own_name - ft_strlen(getpwuid(path->stat->st_uid)->pw_name);
	while (ws > 0)
	{
		ft_putstr(" ");
		ws--;
	}
}