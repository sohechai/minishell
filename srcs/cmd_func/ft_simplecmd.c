/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simplecmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:03:46 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/04 15:37:38 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void		ft_exit()
{
	// pid_t pid;
	ft_printf("exit\n");
	// ft_freetab(cmd);
	// ft_freestruct(st);
	// pid = getpid();
	// kill(pid, SIGQUIT);
	// TODO faire fonction ft_exit qui free proprement tout ce qui a ete alloué
	exit(EXIT_SUCCESS);
}

int				ft_simplecmd(t_struct *st, t_mini *mi, char **envp, size_t n)
{
	char	**cmd;

	st->copyenvp = envp;
	cmd = ft_strtokk(mi->tab_arg[n], " \n\t");
	if (cmd[0] == NULL)
		ft_printf("");
	else if (ft_is_built_in(cmd[0]) == false)
	{
		ft_getabsolutepath(cmd, st);
		ft_execcmd(cmd);
	}
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit();
	else
		ft_exec_built_in(mi, cmd, st, n);
	return (EXIT_SUCCESS);
}
