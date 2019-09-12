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
		ft_putstr(" invalid option -");
		ft_putstr(s);
		write(1, "\n", 1);
		ft_putstr("usage: ft_ls [laASRrtucf] [file ...]\n");
	}
}

void	swap_elem(t_path *p1, t_path *p2)
{
	char		*t_name;
	struct stat *t_stat;

	t_name = p1->name;
	p1->name = p2->name;
	p2->name = t_name;
	t_stat = p1->stat;
	p1->stat = p2->stat;
	p2->stat = t_stat;
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
