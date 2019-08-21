
#include "ft_ls.h"

void print_type(t_path *path)
{
	if(S_ISDIR(path->stat->st_mode))
		ft_putchar('d');
	if(S_ISBLK(path->stat->st_mode))
		ft_putchar('b');
	if(S_ISLNK(path->stat->st_mode))
		ft_putchar('l');
	if(S_ISCHR(path->stat->st_mode))
		ft_putchar('c');
	if (S_ISREG(path->stat->st_mode))
		ft_putchar('-');
	if (S_ISFIFO(path->stat->st_mode))
		ft_putchar('p');
	if (S_ISSOCK(path->stat->st_mode))
		ft_putchar('s');	
}

void ovner_perm(t_path path, char **s)
{
    if (path.stat->st_mode & S_IRUSR)
        *s[0] = 'r';
    else
        *s[0] = '-';
    if (path.stat->st_mode & S_IWUSR)
        *s[1] = 'w';
    else
        *s[1] = '-';
    if (path.stat->st_mode & S_IXUSR)
        *s[2] = 'w';
    else
        *s[2] = '-';
}

void print_permission(t_path path)
{
    char *res = {0};

    // if (path.stat->st_mode & S_IRWXU)
    //     ft_putstr("rwx");

        ovner_perm(path, &res);
        ft_putstr(res);

    

}

void print_name(t_path *path)
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

void printing(t_path *path, char *flags)
{

	t_path *tmp;

	tmp = path;

	if (ft_strrchr(flags, 'l'))
	{
		while (tmp)
		{
			print_type(tmp);
			print_permission(*tmp);
            print_name(tmp);
			
			tmp = tmp->next;
		}
		printf("\n");
	}
}