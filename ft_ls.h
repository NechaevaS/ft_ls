/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 14:02:03 by snechaev          #+#    #+#             */
/*   Updated: 2019/09/24 14:35:14 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdlib.h>
# include <sys/xattr.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include <errno.h>
# include "libft/libft.h"

# define FLAGS		("ARSacflrtu1")
# define SIX_MONTHS	(15778800)

# define COL_IFO	"\x1b[33m"
# define COL_CHR	"\x1b[34;43m"
# define COL_DIR	"\x1b[1m\x1b[36m"
# define COL_BLK	"\x1b[34;46m"
# define COL_REG	"\x1b[0m"
# define COL_LNK	"\x1b[35m"
# define COL_SOCK	"\x1b[32m"
# define COL_EXE	"\x1b[0;31m"
# define COL_CLR	"\x1b[0m"

typedef struct
{
	int				max_lnk;
	int				max_size;
	int				max_group_name;
	int				max_own_name;

}					t_help;

typedef struct		s_path
{
	char			*all_p;
	char			attr;
	char			*link;
	struct stat		*stat;
	char			*name;
	struct s_path	*next;
	t_help			*max;
}					t_path;

typedef struct
{
	int				n_elem;
	int				blk_l;
	int				cols;
	int				rows;
}					t_col;

void				ft_error(const char *s, int n);
t_path				*add_to_path(char *old_p, t_path *path, char *curr);
t_help				*init_max();
void				print_path_name(t_path *path);
int					is_less_a_time(t_path *s1, t_path *s2);
int					is_less_c_time(t_path *s1, t_path *s2);
int					is_less_m_time(t_path *s1, t_path *s2);
t_path				*sort_path(t_path *path, char *flags);
t_path				*sort_f(t_path *p);
void				swap_elem(t_path *p1, t_path *p2);
void				ft_ls(t_path *path, char *flags, int argc);
t_path				*create_new_path(char *path, char *flags);
int					count_blocks(t_path *p);
void				path_del(t_path *p);
t_path				*elem_del(t_path *p);
void				get_max_n(t_path *p);
void				print_column(t_path *p, int argc, int *r);
void				print_type(t_path *path);
void				print_gr_name(t_path *path);
void				print_ow_name(t_path *path);
void				print_permission(t_path path);
void				print_time(t_path *path, char *flags);
void				print_size(t_path *path);
void				print_num_lnk(t_path *path);
void				print_name(t_path *path);
void				print_path(t_path *p, char *flags, int srt, int *r);
void				printing_l(t_path *path, char *flags);
void				printing(t_path *path, char *flags);
#endif
