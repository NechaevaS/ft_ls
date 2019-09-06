/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:44:14 by snechaev          #+#    #+#             */
/*   Updated: 2019/08/26 18:37:06 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void print_type(t_path *path)
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

void print_permission(t_path path)
{
	char res[10];

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

void print_time(t_path *path)
{
	char *t;
	char **arr;
	time_t t_now;

	t_now = time(NULL);
	t = ctime(&path->stat->st_mtime);
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

void print_size(t_path *path)
{
	char *s;
	int len;
	int i;

	s = ft_itoa(path->stat->st_size);
	len = ft_strlen(s);
	i = 5 - len;
	if (len == 5)
	{
		ft_putstr(s);
		return;
	}
	while (i >= 0)
	{
		if ((i + len) == len)
			ft_putstr(s);
		else
			ft_putstr(" ");
		i--;
	}
}

void    print_name(t_path *path, char *flags)
{
    if (!ft_strrchr(flags, 'f'))
    {
        if (S_ISDIR(path->stat->st_mode))
            ft_putstr(COL_DIR);
        if (S_ISLNK(path->stat->st_mode))
            ft_putstr(COL_LNK);
        if (S_ISREG(path->stat->st_mode))
            ft_putstr(COL_REG);
        if (S_ISBLK(path->stat->st_mode))
            ft_putstr(COL_BLK);
        if (path->stat->st_mode & S_IXUSR && S_ISREG(path->stat->st_mode))
            ft_putstr(COL_EXE);
        ft_putstr(path->name);
        ft_putstr(COL_CLR);
    }
    else
        ft_putstr(path->name);
}

void printing_l(t_path *path, char *flags)
{

	if (ft_strrchr(flags, 'l'))
	{

		print_type(path);
		print_permission(*path);
		ft_putstr("  ");
		ft_putchar((path->stat->st_nlink) + '0');
		ft_putstr(" ");
		ft_putstr(getpwuid(path->stat->st_uid)->pw_name);
		ft_putstr("  ");
		ft_putstr(getgrgid(path->stat->st_gid)->gr_name);
		ft_putstr(" ");
		print_size(path);
		ft_putstr(" ");
		print_time(path);
		ft_putstr(" ");
		print_name(path, flags);
		ft_putstr("\n");
	}
}

void	printing(t_path *path, char *flags)
{

	if (ft_strrchr(flags, 'l'))
	{
		printing_l(path, flags);
	}
	else
	{
		print_name(path, flags);
    //    if (!ft_strrchr(flags, '1'))
    //        ft_putstr("  ");
     //   else
     //       ft_putstr("\n");
	}
}
