/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_column.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 16:15:06 by snechaev          #+#    #+#             */
/*   Updated: 2019/09/13 15:59:09 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		path_len(t_path *p, int argc)
{
	int	len;

	len = 0;
	while (p)
	{
		if (argc == 1 && (S_ISDIR(p->stat->st_mode)
			|| S_ISLNK(p->stat->st_mode)))
			p = p->next;
		else
		{
			len++;
			p = p->next;
		}
	}
	return (len);
}

t_path **fill_arr(t_path *p, int argc, t_col col)
{
	int	i;
	t_path **arr;

	i = 0;
	arr = (t_path **)malloc(sizeof(t_path *) * col.n_elem);
	while (i < col.n_elem && p)
	{
		if (argc == 1 && (S_ISDIR(p->stat->st_mode)
			|| S_ISLNK(p->stat->st_mode)))
			p = p->next;
		else
		{
			arr[i] = p;
			p = p->next;
			i++;
		}
	}
	if (i == 0)
		return (NULL);
	return (arr);
}

int		get_max(t_path **arr, int n, int cur, int row)
{
	int	max;
	int	curr;
	int	fin;
	int	start;

	start = cur - row;
	fin = n - row + cur;
	max = 0;
	while (start < fin && arr[start])
	{
		curr = ft_strlen(arr[start]->name);
		if (curr > max)
			max = curr;
		start++;
	}
	return (max + 1);
}

void	print_row(t_col col, t_path **arr, int start)
{
	int	i;
	int	cur;
	int	wsps;

	i = 0;
	cur = start;
	while (i < col.cols && cur < col.n_elem)
	{
		print_name(arr[cur]);
		wsps = col.blk_l - ft_strlen(arr[cur]->name);
		while (wsps > 0)
		{
			write(1, " ", 1);
			wsps--;
		}
		cur = cur + col.rows;
		i++;
	}
	ft_putstr("\n");
}

void	print_column(t_path *p, char *flags, int argc)
{
	t_path			**arr;
	struct winsize	ws;
	t_col			col;
	int				i;
	int				all_len;

	all_len = 0;
	i = 0;
	if (!(col.n_elem = path_len(p, argc)))
		return ;
	if (ioctl(0, TIOCGWINSZ, &ws) != 0)
		return (print_path(p, flags, 0, 0));
	arr = fill_arr(p, argc, col);
	if (arr == NULL)
		return ;
	all_len = (get_max(arr, col.n_elem, 0, 0) + 2) * col.n_elem;
	col.cols = ws.ws_col / get_max(arr, col.n_elem, 0, 0);
	col.blk_l = ws.ws_col / col.cols;
	col.rows = col.n_elem / col.cols + (all_len % (ws.ws_col) ? 1 : 0);
	while (i < col.rows)
	{
		print_row(col, arr, i);
		i++;
	}
}
