#include "ft_ls.h"

void ft_error(const char *s, int n)
{
	write(1, "ft_ls: ", 7);
	//ft_putstr(s);
	//write(1, ": ", 2);
	if (n == 1)
		ft_putstr("No such file or directory\n");
	if (n == 2)
	{
		ft_putstr(" invalid option -");
		ft_putstr(s);
		write(1, "\n", 1);
		ft_putstr("usage: ft_ls [laASRrtucf] [file ...]\n");
	}
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
	return (n_bl/2);
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