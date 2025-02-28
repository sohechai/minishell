/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:28:05 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/12 12:47:37 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	change_loop(t_struct *st, size_t i, size_t n, char c)
{
	i++;
	while (st->tab_arg[n][i] && st->tab_arg[n][i] != c)
	{
		if (ft_strchr(" \t", st->tab_arg[n][i]))
			st->tab_arg[n][i] = -8;
		i++;
	}
	return (i);
}

static void		change_space_char(t_struct *st, size_t i, size_t n)
{
	while (st->tab_arg[n][i])
	{
		if (st->tab_arg[n][i] == '"' || st->tab_arg[n][i] == '\'')
			i = change_loop(st, i, n, st->tab_arg[n][i]) + 1;
		else
			i++;
	}
}

int				ft_pipecmd(t_struct *st, size_t n)
{
	int		i;

	i = 0;
	change_space_char(st, 0, n);
	st->index = 0;
	ft_execpipe(st->tab_arg[n], st);
	return (EXIT_SUCCESS);
}
