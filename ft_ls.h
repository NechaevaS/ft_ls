/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 14:02:03 by snechaev          #+#    #+#             */
/*   Updated: 2019/08/21 17:38:41 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <stdlib.h>
# include <sys/xattr.h>
# include <sys/stat.h>
# include <sys/types.h>
//# include <uuid/uuid.h>
# include <sys/ioctl.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include <errno.h>
# include "libft/libft.h"

# define FLAGS		("laASRrtucf")
# define SIX_MONTHS	(15778800)

typedef struct 		s_path
{
	struct stat		*stat;
	char			*name;
	struct s_path	*next;
}					t_path;

void				ft_error(const char *s, int n);
//t_path				*add_to_path(t_path *path, char *curr);
t_path	*add_to_path(char *old_p,t_path *path, char *curr);
void				print_path_name(t_path *path);
t_path				*sort_path(t_path *path, char *flags);
void				printing_l(t_path *path, char *flags);
void				swap_elem(t_path *p1, t_path *p2);
void				ft_ls(t_path *path, char *flags, int argc);
void				print_path(t_path *p, char *flags);
void				printing(t_path *path, char *flags);
t_path 				*create_new_path(char *path, char *flags);
int					count_blocks(t_path *p);
#endif