/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:16:51 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/04 15:18:56 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			ft_reset_mi(t_struct *st)
{
	st->error = 0;
	st->quote = 0;
	st->nquote = 0;
	st->islast = 0;
	st->op = 0;
	st->semi = 0;
	st->fd = 1;
	st->nbackslash = 0;
	st->nredir = 0;
	ft_freeloop(st);
}

void			ft_free_mi(t_struct *st)
{
	ft_delete(&st->line);
	ft_free_tab(st->tab_arg);
}

void			change_real_char(t_struct *st, size_t n, size_t i)
{
	while (st->tab_arg[n])
	{
		i = 0;
		while (st->tab_arg[n][i])
		{
			if (st->tab_arg[n][i] == '"' || st->tab_arg[n][i] == '\'')
				i = ft_change_char(st->tab_arg[n][i], st, i + 1, n);
			else
				i++;
			if (i >= ft_strlen(st->tab_arg[n]))
				break ;
		}
		n++;
	}
}

size_t			advance(char *str, size_t i, char c)
{
	while (str[i] && str[i] != c)
	{
		i++;
		if (str[i] == '\0')
			break ;
	}
	if (str[i] == c)
		i++;
	return (i);
}

int				check_next_one(char *str, char c)
{
	if (str[1] == c)
		return (1);
	return (0);
}
