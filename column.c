#include "ft_ls.h"

// char **add_to_col_names(t_path *path, int *len)
// {
// 	char **names;
// 	t_path *tmp;
// 	int i = 0;

// 	tmp = path;
// 	while(tmp)
// 	{
// 		(*len)++;
// 		tmp = tmp->next;
// 	}
// 	names = (char**)malloc(sizeof(char *) * (*len));
// 	tmp = path;
// 	while(tmp)
// 	{
// 		names[i] = ft_strdup(tmp->name); 
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	return(names);
// }



// void	print_row(t_col col, int start, int blk)
// {
// 	int i;
// 	int j;
// 	int cur;

// 	i = 0;
// 	cur = start;
// 	while (i < col.cols && cur <)
// 	{
// 		ft_putstr(col.names[cur]);
// 		j = blk - ft_strlen(col.names[cur]);
// 		while(j < blk)
// 		{
// 			write(1, " ", 1);
// 			j++;
// 		}
// 		cur = cur + col.rows;
// 		i++;
// 	}
// 	ft_putstr("\n");
// }

// void print_column(t_path *p, char *flags)
// {
// 	int				w_col;
// 	struct winsize	ws;
// 	int				n_elem;
// 	t_col			col;
// 	int 			i;

// 	n_elem = 0;
// 	col.names = add_to_col_names(p, &n_elem);
// 	w_col = get_max(p);
// 	col.cols = ioctl(0, TIOCGWINSZ, &ws);
// 	if (col.cols != 0)
// 		return (print_path(p, flags));
// 	col.cols = (ws.ws_col / 8) / w_col;
// 	i = 0;
// 	col.rows = n_elem / col.cols + (n_elem % col.cols ? 1 : 0);
// 	while (i < col.rows)
// 	{
// 		print_row(col, i, w_col * 8);
// 		i++;
// 	}
// }
int	path_len(t_path *p)
{
	int len;

	len = 0;
	while(p)
	{
		len++;
		p = p->next;
	}
	return (len);
}

void fill_arr(t_path **arr, t_path *p)
{
	int i = 0;
	while(p)
	{
		arr[i] = p;
		p = p->next;
		i++;
	}	
	arr[i] = NULL;
}

int	get_max(t_path **arr, int n)
{
	int max;
	int	curr;
	int i;
	
	max = 0;
	i = 0;
	while(i < n)
	{
		curr = ft_strlen(arr[i]->name);
		if (curr > max)
			max = curr;
		i++;
		
	}
	return (max);
}

void	print_row(t_col col, t_path **arr, int start, char *flags)
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
		w_col = get_max(arr, col.rows);
		wsps = w_col - ft_strlen(arr[cur]->name);
		while(wsps)
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
	t_path 			**arr;
	struct winsize	ws;
	int				n_elem;
	t_col			col;
	int 			i;
	int				all_len;

	all_len = 0;
	n_elem = path_len(p);
//	printf ("lines %d\n", ws.ws_row);
//  printf ("columns %d\n", ws.ws_col);
	if (ioctl(0, TIOCGWINSZ, &ws) != 0)
		return (printing(p, flags));
	arr = (t_path**)malloc(sizeof(t_path *) * n_elem + 1);
	fill_arr(arr, p);
	i = 0;
	while(i < n_elem)
	{
		all_len = all_len + ft_strlen(arr[i]->name) + 2;
		i++;
	}
	if (all_len <= (ws.ws_col / 8))
	{
		print_path(p,flags);
		return;
	}
	col.rows = all_len / (ws.ws_col / 8) + (all_len % (ws.ws_col / 8) ? 1 : 0);
	col.cols = n_elem / col.rows;
	i = 0;
	while (i < col.rows)
	{
		print_row(col, arr, i, flags);
		i++;
	}
}