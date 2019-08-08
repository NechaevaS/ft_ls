#include "ft_ls.h"

void print_path(t_path *path)
{
	int i = 0;
	while (path)
	{
		printf("%s\n", path->name);
		path = path->next;
		i++;
	}
}