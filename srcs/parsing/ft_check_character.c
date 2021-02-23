/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_character.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:11:44 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/23 15:39:05 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t			ft_change_char(char c, t_mini *mi, size_t i, size_t n)
{
	while (mi->tab_arg[n][i] && mi->tab_arg[n][i] != c)
	{
		if (mi->tab_arg[n][i] == ';')
			mi->tab_arg[n][i] = -2;
		else if (mi->tab_arg[n][i] == '|')
			mi->tab_arg[n][i] = -3;
		else if (mi->tab_arg[n][i] == '>')
			mi->tab_arg[n][i] = -4;
		else if (mi->tab_arg[n][i] == '<')
			mi->tab_arg[n][i] = -5;
		i++;
	}
	return (i);
}

int				check_nquote(char *str, size_t i)
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
		return (ft_error('\'', 1));
	else if (dquote % 2 != 0)
		return (ft_error('"', 1));
	return (1);
}

static size_t	replace(t_mini *mi, t_struct *st, size_t n, size_t i)
{
	while (mi->tab_arg[n][i] && mi->tab_arg[n][i] != '"')
	{
		if (mi->tab_arg[n][i] == '$')
		{
			if ((i = re_env(mi, st, mi->tab_arg[n] + (i + 1), i, n)) == 0)
				return (0);
		}
		i++;
	}
	if (mi->tab_arg[n][i] == '"')
		i++;
	return (i);
}

int				change_char_in_dquote(t_mini *mi,
								t_struct *st, size_t i, size_t n)
{
	while (mi->tab_arg[n])
	{
		i = 0;
		while (mi->tab_arg[n][i])
		{
			if (mi->tab_arg[n][i] == '"')
			{
				if ((i = replace(mi, st, n, i + 1)) == 0)
					return (ft_error('"', 1));
			}
			else if (mi->tab_arg[n][i] == '\'')
			{
				if ((i = advance(mi->tab_arg[n], i + 1, '\'')) == 0)
					return (ft_error('\'', 1));
			}
			else if (mi->tab_arg[n][i] == '$'
				&& !ft_strchr(" \t\0", mi->tab_arg[n][i + 1]))
			{
				if (mi->tab_arg[n][i + 1] == '\0')
					i++;
				else if ((i = re_env(mi, st,
						mi->tab_arg[n] + (i + 1), i, n)) == 0)
					return (0);
			}
			else
				i++;
		}
		n++;
	}
	return (1);
}

int				ft_check_character(t_mini *mi)
{
	size_t i;

	i = 0;
	if (mi->line[0] == '|' || mi->line[0] == ';')
	{
		ft_error(mi->line[0], 0);
		return (0);
	}
	if (!check_nquote(mi->line, 0))
		return (0);
	while (mi->line[i])
	{
		if (mi->line[i] == ';' && mi->line[i + 1] == '|')
			return (ft_error('|', 1));
		if (mi->line[i] == '|' && mi->line[i + 1] == ';')
			return (ft_error(';', 1));
		i++;
	}
	if (!check_pipe(mi))
		return (0);
	return (1);
}
