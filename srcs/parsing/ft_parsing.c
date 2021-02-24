/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:15:37 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/24 14:19:48 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t		ft_search(char *cmd, size_t i)
{
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
			i = advance(cmd, i + 1, cmd[i]);
		else if (cmd[i] == ';')
			return (i);
		else
			i++;
		if (i >= ft_strlen(cmd))
			break ;
	}
	return (i);
}

static char			**clean_spaces(t_mini *mi, size_t n)
{
	size_t		st;
	size_t		end;
	char		**tab;

	if (!(tab = (char**)malloc(sizeof(char*) * (mi->semi + 1))))
		return (NULL);
	while (n < mi->semi && mi->tab_arg[n][0] != '\0')
	{
		st = 0;
		while (mi->tab_arg[n][st])
			st++;
		st = st - 1;
		while (ft_strchr(" ;", mi->tab_arg[n][st]))
			st--;
		end = st + 1;
		st = 0;
		while (mi->tab_arg[n][st] == ' ')
			st++;
		tab[n] = ft_substr(mi->tab_arg[n], st, end);
		n++;
	}
	tab[n] = NULL;
	ft_free_tab(mi->tab_arg);
	return (tab);
}

static void			ft_fill_tab(t_mini *mi, char *cmd, size_t n)
{
	size_t		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
			i = advance(cmd, i + 1, cmd[i]);
		if (cmd[i] == '|')
		{
			mi->tab_pipe[n] = 1;
			break ;
		}
		else
			i++;
		if (i >= ft_strlen(cmd))
			break ;
	}
	if (mi->tab_pipe[n] != 1)
		mi->tab_pipe[n] = 0;
}

static void			ft_separate_cmd(t_mini *mi, size_t i, size_t n)
{
	size_t		tmp;

	tmp = 0;
	mi->tab_pipe = (int *)malloc(sizeof(int) * (mi->semi + 1));
	mi->tab_arg = (char **)malloc(sizeof(char *) * (mi->semi + 1));
	while (n < mi->semi)
	{
		i = ft_search(mi->line, i);
		mi->tab_arg[n] = ft_strndup(mi->line + tmp, i - tmp);
		ft_fill_tab(mi, mi->tab_arg[n], n);
		n++;
		i++;
		if (i >= ft_strlen(mi->line))
			break ;
		while (mi->line[i] == ' ')
			i++;
		tmp = i;
	}
	mi->tab_arg[n] = NULL;
	change_real_char(mi, 0, 0);
	mi->tab_arg = clean_spaces(mi, 0);
}

int					ft_parsing(t_mini *mi, t_struct *st, size_t i)
{
	while (mi->line[i])
	{
		if (mi->line[i] == '"' || mi->line[i] == '\'')
			i = advance(mi->line, i + 1, mi->line[i]);
		if (mi->line[i] == ';')
		{
			if (endline(mi->line, i + 1))
				break ;
			if (mi->line[i] == '|' && endline(mi->line, i + 1))
				if (!print_prompt_waiting(mi, NULL, 0))
					return (0);
			if (mi->line[i] == ';')
				mi->semi++;
		}
		if (i > ft_strlen(mi->line))
			break ;
		i++;
	}
	mi->semi++;
	ft_separate_cmd(mi, 0, 0);
	if (!change_char_in_dquote(mi, st, 0, 0))
		return (0);
	return (1);
}
