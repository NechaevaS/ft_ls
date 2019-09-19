/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 14:19:47 by snechaev          #+#    #+#             */
/*   Updated: 2019/09/19 11:03:31 by snechaev         ###   ########.fr       */
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
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], "--"))
			i += 1;
		else if (argv[i][0] == '-')
		{
			check_add_flag(argv[i], flags);
			continue ;
		}
		break ;
	}
	while (++i <= argc && argc != 1)
		path = add_to_path(0, path, argv[i - 1]);
	return (path);
}

t_help	*init_max()
{
	t_help	*max;

	max = (t_help *)malloc(sizeof(t_help));
	max->max_lnk = 0;
	max->max_size = 0;
	max->max_group_name = 0;
	max->max_own_name = 0;
	return (max);
}

int		main(int argc, char **argv)
{
	char	*flags;
	t_path	*path;
	t_help	*max;

	flags = ft_strnew((int)ft_strlen(FLAGS));
	max = init_max();
	if (!flags)
		return (3);
	else
	{
		path = parse_args(argv, argc, flags);
		if (!path)
		{
			path = add_to_path(0, path, ".");
			ft_ls(path, flags, 0, max);
		}
		else
		{
			path = sort_path(path, flags);
			ft_ls(path, flags, 1, max);
		}
	}
	//system("leaks ft_ls");
	return (0);
}
