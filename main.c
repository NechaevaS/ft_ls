/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 14:19:47 by snechaev          #+#    #+#             */
/*   Updated: 2019/08/21 17:24:27 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	check_add_flag(char *curr, char *flags)
{
	int		i;

	i = 1;
	while (curr[i])
	{
		if (!ft_strrchr(FLAGS, curr[i]))
		{
			ft_error(curr, 2);
			return (exit(1));
		}
		else if (!ft_strrchr(flags, curr[i]))
			ft_strncat(flags, &(curr[i]), 1);
		i++;
	}
	return ;
}

t_path	*parse_args(char **argv, int argc, char *flags)
{
	int		i;
	t_path	*path;

	i = 0;
	path = NULL;
	while (i < argc)
	{
		i++;
		if (!ft_strcmp(argv[i], "--"))
			i += 1;
		else if (argv[i][0] == '-')
		{
			check_add_flag(argv[i], flags);
			continue ;
		}
		break ;
	}
	while (i < argc)
	{
		path = add_to_path(path, argv[i]);
		i++;
	}
	return (path);
}

void	print_path(t_path *p)
{
	while (p)
	{
		printf("%s ", p->name);
		p = p->next;
	}
	ft_putstr("\n");
}

int		main(int argc, char **argv)
{
	char	*flags;
	t_path	*path;

	flags = ft_strnew((int)ft_strlen(FLAGS));
	if (!flags)
		return (3);
	else
	{
		path = parse_args(argv, argc, flags);
		if (!path)
			path = add_to_path(path, ".");
	//	print_path(path);
		path = sort_path(path, flags);
	//	print_path(path);
		printing(path, flags);
	}
	return (0);
}
