/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_char_in_dquote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 13:43:52 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/12 13:44:17 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	replace(t_struct *st, size_t n, size_t i)
{
	while (st->tab_arg[n][i] && st->tab_arg[n][i] != '"')
	{
		if (st->tab_arg[n][i] == '$' && (ft_isalnum(st->tab_arg[n][i + 1])
			|| st->tab_arg[n][i + 1] == '?' || st->tab_arg[n][i + 1] == '_'))
		{
			if ((i = re_env(st, st->tab_arg[n] + (i + 1), i, n)) == 0)
				return (0);
		}
		if (i >= ft_strlen(st->tab_arg[n]))
			break ;
		i++;
	}
	if (st->tab_arg[n][i] == '"')
		i++;
	return (i);
}

static int		change_loop(t_struct *st, size_t i, size_t n)
{
	while (st->tab_arg[n][i])
	{
		if (st->tab_arg[n][i] == '"' && (i = replace(st, n, i + 1)) == 0)
			return (ft_error('"', 1));
		else if (st->tab_arg[n][i] == '\''
			&& !(i = advance(st->tab_arg[n], i + 1, '\'')))
			return (ft_error('\'', 1));
		else if (st->tab_arg[n][i] == '$'
			&& !ft_strchr(" \t\0", st->tab_arg[n][i + 1]))
		{
			if (st->tab_arg[n][i + 1] == '\0')
				i++;
			else if ((i = re_env(st, st->tab_arg[n] + (i + 1), i, n)) == 0)
				return (0);
		}
		else
			i++;
		if (i >= ft_strlen(st->tab_arg[n]))
			break ;
	}
	return (1);
}

int				change_char_in_dquote(t_struct *st, size_t i, size_t n)
{
	while (st->tab_arg[n])
	{
		i = 0;
		if (!change_loop(st, i, n))
			return (0);
		n++;
	}
	return (1);
}
