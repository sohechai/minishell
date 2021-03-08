/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:54:59 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/08 13:33:49 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int			what_after(char *str, size_t i, t_struct *st, char c)
{
	while (!ft_isalnum(str[i]))
	{
		if (str[i] == c)
		{
			if (str[i + 1] == c)
			{
				return (ft_error(c, 2, st));
			}
			return (ft_error(c, 1, st));
		}
		i++;
	}
	return (1);
}

static size_t		count_redirr(t_struct *st, size_t i, size_t n, size_t j)
{
	st->nredir = 1;
	while (st->tab_arg[n][i] == '>' || st->tab_arg[n][i] == ' ')
	{
		if (st->tab_arg[n][i] == '>')
			st->nredir++;
		if (st->tab_arg[n][i] == '<')
		{
			if (st->line[i + 1] == '<')
				j = 2;
			return (ft_error('<', j, st));
		}
		if (st->nredir == 3 && st->tab_arg[n][i + 1] != '>')
			return (ft_error('>', 1, st));
		if (st->nredir > 3)
			return (ft_error('>', 2, st));
		if (st->tab_arg[n][i] == ' ')
		{
			if (!what_after(st->tab_arg[n], i + 1, st, '>'))
				return (0);
		}
		i++;
	}
	return (i);
}

static size_t		count_redirl(t_struct *st, size_t i, size_t n, size_t j)
{
	st->nredir = 1;
	j = 0;
	while (st->tab_arg[n][i] == '<' || st->tab_arg[n][i] == ' ')
	{
		if (st->tab_arg[n][i] == '<')
		{
			st->nredir++;
			if (st->tab_arg[n][i + 1] == '<')
				j++;
			return (ft_error('<', j, st));
		}
		if (st->tab_arg[n][i] == ' ')
		{
			if (!what_after(st->tab_arg[n], i + 1, st, '<'))
				return (0);
		}
		i++;
	}
	return (i);
}

int					check_redirect(t_struct *st, size_t i, size_t n)
{
	while (st->tab_arg[n])
	{
		i = 0;
		while (st->tab_arg[n][i])
		{
			if (st->tab_arg[n][i] == '>')
			{
				if ((i = count_redirr(st, i + 1, n, 1)) == 0)
					return (0);
			}
			else if (st->tab_arg[n][i] == '<')
			{
				if ((i = count_redirl(st, i + 1, n, 1)) == 0)
					return (0);
			}
			else
				i++;
			if (i >= ft_strlen(st->tab_arg[n]))
				break ;
		}
		n++;
	}
	return (1);
}
