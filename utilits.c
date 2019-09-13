#include "ft_ls.h"

void ft_error(const char *s, int n)
{
	write(1, "ft_ls: ", 7);

	if (n == 1)
	{
			ft_putstr(s);
			write(1, ": ", 2);
		ft_putstr("No such file or directory\n");
	}
	if (n == 2)
	{
		ft_putstr(" illegal option -");
		ft_putstr(s);
		write(1, "\n", 1);
		ft_putstr("usage: ft_ls [laASRrtucf] [file ...]\n");
	}
}

void	swap_elem(t_path *p1, t_path *p2)
{
	char			*t_name;
	struct stat 	*t_stat;
	char			*t_all_p;
	char			t_attr;
	char			*t_link;

	t_name = p1->name;
	p1->name = p2->name;
	p2->name = t_name;
	t_stat = p1->stat;
	p1->stat = p2->stat;
	p2->stat = t_stat;
	t_all_p = p1->all_p;
	p1->all_p = p2->all_p;
	p2->all_p = t_all_p;
	t_attr = p1->attr;
	p1->attr = p2->attr;
	p2->attr = t_attr;
	t_link = p1->link;
	p1->link = p2->link;
	p2->link = t_link;
}

int	count_blocks(t_path *p)
{
	int n_bl;

	n_bl = 0;
	while (p)
	{
		n_bl = n_bl + (p->stat->st_blocks);
		p = p->next;
	}
	return (n_bl);
}

int	get_max_n(t_path *p, int n)
{
	unsigned int	max_lnk;
	unsigned int	max_size;
	int				res;

	max_lnk = 0;
	max_size = 0;
	while(p)
	{
		if (p->stat->st_nlink > max_lnk)
			max_lnk = p->stat->st_nlink;
		if (p->stat->st_size > max_size)
			max_size = p->stat->st_size;
		p = p->next;
	}
	if (n == 1)
		res = ft_strlen(ft_itoa(max_lnk));
	if (n == 2)
		res = ft_strlen(ft_itoa(max_size));
	return (res);
}

t_path		*path_del(t_path *p)
{
	t_path	*tmp;

	if (!p)
		tmp = NULL;
	else
		tmp = p->next;
	if (p || p->next)
	{
		free(p->name);
		free(p->stat);
		free(p);
		p = NULL;
	}
	return (tmp);
}
