/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:54:59 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/03 17:50:36 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int			what_after(char *str, size_t i)
{
	while (str[i])
	{
		if (str[i] == '>')
		{
			if (str[i + 1] == '>')
				return (ft_error('>', 2));
			return (ft_error('>', 1));
		}
		i++;
	}
	return (1);
}

static size_t		count_redirr(t_struct *st, size_t i,size_t n)
{
	int		j;

	j = 1;
	st->nredir = 1;
	while (st->tab_arg[n][i])
	{
		if (st->tab_arg[n][i] == '>')
			st->nredir++;
		if (st->tab_arg[n][i] == '<')
		{
			if (st->line[i + 1] == '<')
				j = 2;
			return (ft_error('<', j));
		}
		if (st->nredir == 3 && st->tab_arg[n][i + 1] != '>')
			return (ft_error('>', 1));
		if (st->nredir > 3)
			return (ft_error('>', 2));
		if (st->tab_arg[n][i] == ' ')
		{
			if (!what_after(st->tab_arg[n], i + 1))
				return (0);
		}
		i++;
	}
	return (i);
}

static size_t		count_redirl(t_struct *st, size_t i, size_t n)
{
	size_t		j;

	j = 1;
	while (st->tab_arg[n][i])
	{
		if (st->tab_arg[n][i] == '<')
		{
			if (st->tab_arg[n][i + 1] == '<')
				j++;
			return (ft_error('<', j));
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
				if ((i = count_redirr(st, i + 1, n)) == 0)
					return (0);
			}
			else if (st->tab_arg[n][i] == '<')
			{
				if ((i = count_redirl(st, i + 1, n)) == 0)
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
