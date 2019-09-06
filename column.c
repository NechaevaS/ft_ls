#include "ft_ls.h"

int path_len(t_path *p)
{
	int len;

	len = 0;
	while (p)
	{
		len++;
		p = p->next;
	}
	return (len);
}

void fill_arr(t_path **arr, t_path *p)
{
	int i = 0;
	while (p)
	{
		arr[i] = p;
		p = p->next;
		i++;
	}
	arr[i] = NULL;
}

int get_max(t_path **arr, int n, int cur, int row)
{
	int max;
	int curr;
	int fin;
	int start;

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
	return (max);
}

void print_row(t_col col, t_path **arr, int start, char *flags)
{
	int i;
	int w_col;
	int cur;
	int wsps;

	i = 0;
	cur = start;
	while (i < col.cols && arr[cur])
	{
		print_name(arr[cur], flags);
		w_col = get_max(arr, col.rows, cur, start) + 2;
		wsps = w_col - ft_strlen(arr[cur]->name);
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

void print_column(t_path *p, char *flags)
{
	t_path **arr;
	struct winsize ws;
	int n_elem;
	t_col col;
	int i;
	int all_len;

	all_len = 0;
	n_elem = path_len(p);
	if (ioctl(0, TIOCGWINSZ, &ws) != 0)
		return (print_path(p, flags, 0));
	arr = (t_path **)malloc(sizeof(t_path *) * n_elem + 1);
	fill_arr(arr, p);
	i = 0;
	while (i < n_elem)
	{
		all_len = all_len + ft_strlen(arr[i]->name) + 2;
		i++;
	}
	if (all_len < (ws.ws_col))
	{
		print_path(p, flags, 1);
		return;
	}
	col.rows = all_len / (ws.ws_col) + (all_len % (ws.ws_col) ? 1 : 0);
	col.cols = n_elem / col.rows;
	if (col.cols * get_max(arr, n_elem, 0, 0) > ws.ws_col)
	{
		col.cols--;
		col.rows = n_elem / col.cols;
	}
	i = 0;
	while (i < col.rows)
	{
		print_row(col, arr, i, flags);
		i++;
	}
}