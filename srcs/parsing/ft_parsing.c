/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:15:37 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/04 15:15:53 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t		ft_search(char *cmd, char *s)
{
	size_t		i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(s, cmd[i]))
			return (i);
		i++;
	}
	return (i);
}

static char			**clean_spaces(t_mini *mi)
{
	size_t		n;
	size_t		st;
	size_t		end;
	char		**tab;

	n = 0;
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
		i += ft_search(mi->line + i, ";|\0");
		mi->tab_arg[n] = ft_strndup(mi->line + tmp, i - tmp);
		ft_fill_tab(mi->line[i], mi->tab_pipe, n, mi->semi);
		n++;
		if (mi->line[i] == '\0')
			break ;
		i++;
		while (mi->line[i] == ' ')
			i++;
		tmp = i;
	}
	mi->tab_arg[n] = NULL;
	mi->tab_arg = clean_spaces(mi);
}

int					ft_parsing(t_mini *mi)
{
	size_t		i;

	i = 0;
	while (mi->line[i])
	{
		if (mi->line[i] == '|' || mi->line[i] == ';')
		{
			if (mi->line[i] == ';' && endline(mi->line, i + 1))
				break ;
			if (mi->line[i] == '|' && endline(mi->line, i + 1))
				if (!print_prompt_waiting(mi, NULL, 0))
					return (0);
			if (mi->line[i] == ';' && mi->line[i + 1] == ';')
			{
				ft_error(';', 1);
				return (0);
			}
			mi->semi++;
		}
		i++;
	}
	mi->semi++;
	ft_separate_cmd(mi, 0, 0);
	ft_recover_cmd(mi);
	return (1);
}
