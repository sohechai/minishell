/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execpipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:33:59 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/10 13:37:30 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_checkredir(t_struct *st)
{
	char *tmp;

	ft_redirection(st->command[st->index], st);
	if (st->redirection != 0)
	{
		tmp = st->command[st->index];
		st->command[st->index] = ft_substr(tmp, 0,
				ft_strlenuntilredir(tmp));
		free(tmp);
	}
	st->parsecmd = ft_strtokk(st->command[st->index], " \n\t");
}

void		ft_execpipecmd(t_struct *st)
{
	if (ft_is_built_in(st->parsecmd[0]) == 0)
	{
		ft_getabsolutepath(st->parsecmd, st);
		ft_execcmd(st, st->command[st->index], st->parsecmd);
	}
	else
		ft_exec_built_in(st->parsecmd, st);
	exit(EXIT_FAILURE);
}

void		ft_pipeerror(t_struct *st)
{
	if ((st->pid = fork()) == -1)
	{
		ft_printf("fork error\n");
		exit(EXIT_FAILURE);
	}
}

void		execpipeloop(t_struct *st)
{
	int		pipefd[2];

	ft_checkredir(st);
	pipe(pipefd);
	ft_pipeerror(st);
	if (st->pid == 0)
	{
		dup2(st->fdinput, STDIN);
		if ((st->command[st->index + 1]) != NULL)
			dup2(pipefd[1], STDOUT);
		close(pipefd[0]);
		ft_execpipecmd(st);
	}
	else
	{
		wait(NULL);
		close(pipefd[1]);
		st->fdinput = pipefd[0];
		st->index++;
	}
	if (st->newfd != NULL)
		ft_delete(&st->newfd);
	ft_freetab(st->parsecmd);
}

void		ft_execpipe(char *cmd, t_struct *st)
{
	st->command = ft_strtokk(cmd, "|");
	st->fdinput = 0;
	while (st->command[st->index] != NULL)
		execpipeloop(st);
	ft_freetab(st->command);
}
