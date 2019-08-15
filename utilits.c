#include "ft_ls.h"

void print_path(t_path *path)
{
	t_path *tmp;

	tmp = path;
	while (tmp)
	{
		printf("%s  ", tmp->name);
		tmp = tmp->next;
	}
	printf("\n");
}

void	ft_error(const char *s, int n)
{
	write(1, "ft_ls: ", 7);
	ft_putstr(s);
	write(1, ": ", 2);
	if (n == 1)
		ft_putstr("No such file or directory\n");
	if (n == 2)
	{
		ft_putstr("illegal option --");
		ft_putstr(s);
		write(1, "\n", 1);
		ft_putstr("usage: ft_ls [laARrtT] [file ...]\n");
	}
}