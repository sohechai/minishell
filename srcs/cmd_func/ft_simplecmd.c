/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simplecmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:03:46 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/17 23:19:41 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				ft_lenuntilspace(int i, char *str)
{
	int count;

	count = 0;
	while(str[i] != '\0')
	{
		i++;
		count++;
		if (str[i] == ' ')
			return (count);
	}
	return (count);
}

int				ft_exit(char *cmd, t_struct *st)
{
	int		i;
	int		fd;

	i = 0;
	ft_printf("exit\n");
	if (st->redirection == DOUBLERED || st->redirection == SIMPLERED)
		fd = open(st->newfd, O_CREAT | O_RDWR | O_APPEND, 0640);
	while (cmd[i])
	{
		if (cmd[i] == ' ')
		{
			while (cmd[i] == ' ')
				i++;
			if (ft_isalpha(cmd[i]) != 0)
			{
				ft_printf("exit: %s : argument numérique nécessaire\n",
						ft_substr(cmd, i, ft_lenuntilspace(i, cmd)));
				break ;
			}
		}
		i++;
	}
	//ft_freetab(st->copyenvp);
	ft_freestruct(st);
	// TODO faire fonction ft_exit qui free proprement tout ce qui a ete alloué
	exit(st->exitstatus);
	return (EXIT_SUCCESS);
}

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
	if(str[i - 1] == c)
		return (1);
	return (0);
}

int				ft_simplecmd(t_struct *st, t_mini *mi, char **envp, size_t n)
{
	char	**cmd;

	st->copyenvp = envp;
	if ((ft_strchr(mi->tab_arg[n], '"') || ft_strchr(mi->tab_arg[n], '\'')) &&
		ft_checkquote(mi->tab_arg[n]) == 1)
		cmd = ft_strtokk(mi->tab_arg[n], "\"'");
	else if ((ft_strchr(mi->tab_arg[n], '"') || ft_strchr(mi->tab_arg[n], '\'')) &&
		ft_checkquote(mi->tab_arg[n]) == -1)
		cmd = ft_strtokk(mi->tab_arg[n], " \n\t\"'");
	else
		cmd = ft_strtokk(mi->tab_arg[n], " \n\t");
	if (cmd[0] == NULL)
		ft_printf("");
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(mi->tab_arg[n], st);
	else if (ft_is_built_in(cmd[0]) == false)
	{
		st->printerror = ft_strdup(cmd[0]);
		ft_getabsolutepath(cmd, st);
		ft_execcmd(st, st->printerror, cmd);
		//free(st->printerror); TODO <- free
	}
	else
		ft_exec_built_in(mi, cmd, st, n);
	return (EXIT_SUCCESS);
}
