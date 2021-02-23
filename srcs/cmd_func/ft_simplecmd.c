/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simplecmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:03:46 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/23 15:35:55 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				ft_checkquote(char *str)
{
	int			i;
	int			c;

	i = 0;
	if (str[0] == 34 || str[0] == 39)
		c = str[0];
	while (str[i])
	{
		if (str[0] != c)
			return (0);
		if (str[i] == c && str[i + 1] == ' ')
			return (-1);
		i++;
	}
	if (str[i - 1] == c)
		return (1);
	return (0);
}

static size_t	change_loop(t_mini *mi, size_t i, size_t n, char c)
{
	i++;
	while (mi->tab_arg[n][i] && mi->tab_arg[n][i] != c)
	{
		if (ft_strchr(" \t", mi->tab_arg[n][i]))
			mi->tab_arg[n][i] = -8;
		i++;
	}
	return (i);
}

static void		change_space_char(t_mini *mi, size_t i, size_t n)
{
	while (mi->tab_arg[n][i])
	{
		if (mi->tab_arg[n][i] == '"' || mi->tab_arg[n][i] == '\'')
			i = change_loop(mi, i, n, mi->tab_arg[n][i]) + 1;
		else
			i++;
	}
}

int				ft_simplecmd(t_struct *st, t_mini *mi, char **envp, size_t n)
{
	char	**cmd;

	st->copyenvp = envp;
	change_space_char(mi, 0, n);
	cmd = ft_strtokk(mi->tab_arg[n], " \t\n");
	cmd = rechange_character(cmd, 0, 0);
	cmd = remove_quote(cmd, 0);
	if (cmd[0] == NULL || !cmd[0][0])
		ft_printf("");
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(mi->tab_arg[n], st);
	else if (ft_is_built_in(cmd[0]) == false)
	{
		st->printerror = ft_strdup(cmd[0]);
		ft_getabsolutepath(cmd, st);
		ft_execcmd(st, st->printerror, cmd);
		free(st->printerror);
	}
	else
		ft_exec_built_in(mi, cmd, st);
	ft_free_tab(cmd);
	return (EXIT_SUCCESS);
}
