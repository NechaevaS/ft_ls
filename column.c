/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 16:15:06 by snechaev          #+#    #+#             */
/*   Updated: 2019/09/09 16:15:11 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		path_len(t_path *p)
{
	int	len;

	len = 0;
	while (p)
	{
		len++;
		p = p->next;
	}
	return (len);
}

void	fill_arr(t_path **arr, t_path *p)
{
	int	i;

	i = 0;
	while (p)
	{
		arr[i] = p;
		p = p->next;
		i++;
	}
	arr[i] = NULL;
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

void	print_row(t_col col, t_path **arr, int start, char *flags)
{
	int	i;
	int	cur;
	int	wsps;

	i = 0;
	cur = start;
	while (i < col.cols && arr[cur])
	{
		print_name(arr[cur], flags);
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

void	print_column(t_path *p, char *flags)
{
	t_path			**arr;
	struct winsize	ws;
	t_col			col;
	int				i;
	int				all_len;

	all_len = 0;
	i = 0;
	col.n_elem = path_len(p);
	if (ioctl(0, TIOCGWINSZ, &ws) != 0)
		return (print_path(p, flags, 0));
	arr = (t_path **)malloc(sizeof(t_path *) * col.n_elem + 1);
	fill_arr(arr, p);
	all_len = (get_max(arr, col.n_elem, 0, 0) + 2) * col.n_elem;
	col.cols = ws.ws_col / get_max(arr, col.n_elem, 0, 0);
	col.blk_l = ws.ws_col / col.cols;
	col.rows = col.n_elem / col.cols + (all_len % (ws.ws_col) ? 1 : 0);
	while (i < col.rows)
	{
		print_row(col, arr, i, flags);
		i++;
	}
}
