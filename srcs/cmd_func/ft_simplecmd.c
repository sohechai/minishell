/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simplecmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:03:46 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/16 12:31:59 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				ft_exit(void)
{
	// pid_t pid;
	ft_printf("exit\n");
	//ft_freetab(st->copyenvp);
	// ft_freestruct(st);
	// TODO faire fonction ft_exit qui free proprement tout ce qui a ete alloué
	exit(0);
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
	// en dessous je fais le tri pour savoir comment couper la commande en fonction des quotes etc
	// je pensais que c'etait du a ca que par ex : echo "\"salut\"" donnait \salut\ au lieu de "salut"
	// mais non puisque j'ai remis comme c'etait avant et le resultat de la commande reste le mm 
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
	if (!ft_strcmp(cmd[0], "exit"))
		ft_exit();
	else if (ft_is_built_in(cmd[0]) == false)
	{
		st->printerror = ft_strdup(cmd[0]);
		ft_getabsolutepath(cmd, st);
		ft_execcmd(st, st->printerror, cmd);
		free(st->printerror);
	}
	else
	{
		ft_exec_built_in(mi, cmd, st, n);
	}
	// printf("exit status = %d\n", st->exitstatus);
	return (EXIT_SUCCESS);
}
