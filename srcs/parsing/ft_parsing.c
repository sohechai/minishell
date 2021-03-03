/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:15:37 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/03 17:10:05 by sofiahechai      ###   ########lyon.fr   */
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

static char			**clean_spaces(t_struct *st, size_t n)
{
	size_t		start;
	size_t		end;
	char		**tab;

	if (!(tab = ft_calloc(sizeof(char*), (st->semi + 1))))
		return (NULL);
	while (n < st->semi && st->tab_arg[n][0] != '\0')
	{
		start = 0;
		while (st->tab_arg[n][start])
			start++;
		start = start - 1;
		while (ft_strchr(" ;", st->tab_arg[n][start]))
			start--;
		end = start + 1;
		start = 0;
		while (st->tab_arg[n][start] == ' ')
			start++;
		tab[n] = ft_substr(st->tab_arg[n], start, end);
		n++;
	}
	tab[n] = NULL;
	ft_freetab(st->tab_arg);
	return (tab);
}

static void			ft_fill_tab(t_struct *st, char *cmd, size_t n)
{
	size_t		i;

	i = 0;
	st->tab_pipe[n] = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
			i = advance(cmd, i + 1, cmd[i]);
		if (cmd[i] == '|')
		{
			st->tab_pipe[n] = 1;
			break ;
		}
		else
			i++;
		if (i >= ft_strlen(cmd))
			break ;
	}
}

static void			ft_separate_cmd(t_struct *st, size_t i, size_t n)
{
	size_t		tmp;

	tmp = 0;
	st->tab_pipe = (int *)malloc(sizeof(int) * (st->semi + 1));
	st->tab_arg = (char **)malloc(sizeof(char *) * (st->semi + 1));
	while (n < st->semi)
	{
		i = ft_search(st->line, i);
		st->tab_arg[n] = ft_strndup(st->line + tmp, i - tmp);
		ft_fill_tab(st, st->tab_arg[n], n);
		n++;
		i++;
		if (i >= ft_strlen(st->line))
			break ;
		while (st->line[i] == ' ')
			i++;
		tmp = i;
	}
	st->tab_arg[n] = NULL;
	change_real_char(st, 0, 0);
	st->tab_arg = clean_spaces(st, 0);
}

int					ft_parsing(t_struct *st, size_t i)
{
	while (st->line[i])
	{
		if (st->line[i] == '"' || st->line[i] == '\'')
			i = advance(st->line, i + 1, st->line[i]);
		if (st->line[i] == ';')
		{
			if (endline(st->line, i + 1))
				break ;
			if (st->line[i] == '|' && endline(st->line, i + 1))
				if (!print_prompt_waiting(st, NULL, 0))
					return (0);
			if (st->line[i] == ';')
				st->semi++;
		}
		if (i >= ft_strlen(st->line))
			break ;
		i++;
	}
	st->semi++;
	ft_separate_cmd(st, 0, 0);
	if (!check_redirect(st, 0, 0) || !change_char_in_dquote(st, 0, 0))
	{
		ft_reset_mi(st);
		return (0);
	}
	return (1);
}
