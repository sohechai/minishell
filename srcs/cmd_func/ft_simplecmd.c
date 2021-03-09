/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simplecmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:03:46 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/09 17:08:57 by sohechai         ###   ########lyon.fr   */
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

static size_t	change_loop(t_struct *st, size_t i, size_t n, char c)
{
	i++;
	while (st->tab_arg[n][i] && st->tab_arg[n][i] != c)
	{
		if (ft_strchr(" \t", st->tab_arg[n][i]))
			st->tab_arg[n][i] = -8;
		i++;
	}
	return (i);
}

static void		change_space_char(t_struct *st, size_t i, size_t n)
{
	while (st->tab_arg[n][i])
	{
		if (st->tab_arg[n][i] == '"' || st->tab_arg[n][i] == '\'')
			i = change_loop(st, i, n, st->tab_arg[n][i]) + 1;
		else
			i++;
	}
}

void			ft_searchpath(char *path)
{
	struct stat buffer;
	int			exist;

	exist = stat(path, &buffer);
	if (exist == 0)
		ft_printf("minishell: %s : Is a directory\n", path);
	else
		ft_printf("minishell: %s: No such file or directory\n", path);
}

int				ft_simplecmd(t_struct *st, size_t n)
{
	char	**cmd;

	change_space_char(st, 0, n);
	cmd = ft_strtokk(st->tab_arg[n], " \t\n");
	cmd = rechange_character(cmd, 0, 0);
	cmd = remove_quote(cmd, 0);
	if (cmd[0] == NULL || !cmd[0][0])
		ft_printf("");
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(st->tab_arg[n], st);
	else if (ft_strchr(cmd[0], '/') && ft_strncmp(cmd[0], "./", 2))
		ft_searchpath(cmd[0]);
	else if (ft_is_built_in(cmd[0]) == false)
	{
		st->printerror = ft_strdup(cmd[0]);
		if (ft_getabsolutepath(cmd, st) == 1)
			ft_execcmd(st, st->printerror, cmd);
		free(st->printerror);
	}
	else
		ft_exec_built_in(cmd, st);
	ft_freetab(cmd);
	return (EXIT_SUCCESS);
}
