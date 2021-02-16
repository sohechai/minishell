/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:15:37 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/16 12:07:55 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t		ft_search(char *cmd, size_t i)
{
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
			i = advance(cmd, i + 1, cmd[i]);
		else if (cmd[i] == '|' || cmd[i] == ';')
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
		while (ft_strchr(" ;|", mi->tab_arg[n][st]))
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

static void			ft_fill_tab(char c, int tab[], size_t n, size_t semi)
{
	if (c == '|')
		tab[n] = 1;
	else if (n == semi)
		tab[n] = -1;
	else
		tab[n] = 0;
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
		mi->tab_arg[n] = ft_strndup(mi->line + tmp, i);
		ft_fill_tab(mi->line[i], mi->tab_pipe, n, mi->semi);
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

int					ft_parsing(t_mini *mi, size_t i)
{
	while (mi->line[i])
	{
		if (mi->line[i] == '"' || mi->line[i] == '\'')
			i = advance(mi->line, i + 1, mi->line[i]);
		if (mi->line[i] == '|' || mi->line[i] == ';')
		{
			if (mi->line[i] == ';' && endline(mi->line, i + 1))
				break ;
			if (mi->line[i] == '|' && endline(mi->line, i + 1))
				if (!print_prompt_waiting(mi, NULL, 0))
					return (0);
			if (mi->line[i] == ';' && mi->line[i + 1] == ';')
				return (ft_error(';', 1));
			mi->semi++;
		}
		if (i > ft_strlen(mi->line))
			break ;
		i++;
	}
	mi->semi++;
	ft_separate_cmd(mi, 0, 0);
	if (!change_char_in_dquote(mi, 0, 0))
		return (0);
	ft_recover_cmd(mi);
	return (1);
}
