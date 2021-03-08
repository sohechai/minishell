/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_character.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:11:44 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/08 13:34:27 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t			ft_change_char(char c, t_struct *st, size_t i, size_t n)
{
	while (st->tab_arg[n][i] && st->tab_arg[n][i] != c)
	{
		if (st->tab_arg[n][i] == ';')
			st->tab_arg[n][i] = -2;
		else if (st->tab_arg[n][i] == '|')
			st->tab_arg[n][i] = -3;
		else if (st->tab_arg[n][i] == '>')
			st->tab_arg[n][i] = -4;
		else if (st->tab_arg[n][i] == '<')
			st->tab_arg[n][i] = -5;
		i++;
	}
	return (i);
}

int				check_nquote(char *str, size_t i, t_struct *st)
{
	int		dquote;
	int		squote;

	dquote = 0;
	squote = 0;
	while (str[i])
	{
		if (str[i] == '"')
			dquote++;
		else if (str[i] == '\'')
			squote++;
		i++;
	}
	if (squote % 2 != 0)
		return (ft_error('\'', 1, st));
	else if (dquote % 2 != 0)
		return (ft_error('"', 1, st));
	return (1);
}

static size_t	replace(t_struct *st, size_t n, size_t i)
{
	while (st->tab_arg[n][i] && st->tab_arg[n][i] != '"')
	{
		if (st->tab_arg[n][i] == '$' && (ft_isalnum(st->tab_arg[n][i + 1])
			|| st->tab_arg[n][i + 1] == '?'))
		{
			if ((i = re_env(st, st->tab_arg[n] + (i + 1), i, n)) == 0)
				return (0);
		}
		i++;
	}
	if (st->tab_arg[n][i] == '"')
		i++;
	return (i);
}

int				change_char_in_dquote(t_struct *st, size_t i, size_t n)
{
	while (st->tab_arg[n])
	{
		i = 0;
		while (st->tab_arg[n][i])
		{
			if (st->tab_arg[n][i] == '"')
			{
				if ((i = replace(st, n, i + 1)) == 0)
					return (ft_error('"', 1, st));
			}
			else if (st->tab_arg[n][i] == '\'')
			{
				if ((i = advance(st->tab_arg[n], i + 1, '\'')) == 0)
					return (ft_error('\'', 1, st));
			}
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
		}
		n++;
	}
	return (1);
}

int				ft_check_character(t_struct *st)
{
	size_t i;

	i = 0;
	if (st->line[0] == '|' || st->line[0] == ';')
	{
		ft_error(st->line[0], 0, st);
		return (0);
	}
	if (!check_nquote(st->line, 0, st))
		return (0);
	while (st->line[i])
	{
		if (st->line[i] == '"' || st->line[i] == '\'')
			i = advance(st->line, i + 1, st->line[i]);
		if (st->line[i] == ';' && st->line[i + 1] == '|')
			return (ft_error('|', 1, st));
		if (st->line[i] == '|' && st->line[i + 1] == ';')
			return (ft_error(';', 1, st));
		if (st->line[i] == ';' && st->line[i + 1] == ';')
			return (ft_error(';', 1, st));
		if (i >= ft_strlen(st->line))
			break ;
		i++;
	}
	if (!check_pipe(st))
		return (0);
	return (1);
}
