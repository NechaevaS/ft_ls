/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snechaev <snechaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 14:32:20 by snechaev          #+#    #+#             */
/*   Updated: 2019/07/31 14:37:28 by snechaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_flags *init_flags()
{
	t_flags *flags;

	flags = (t_flags *)malloc(sizeof(t_flags));
	flags->a = 0;
	flags->l = 0;
	flags->R = 0;
	flags->r = 0;
	flags->t = 0;

	return (flags);
}