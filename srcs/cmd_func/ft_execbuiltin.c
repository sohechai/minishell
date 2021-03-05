/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execbuiltin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:25:24 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/05 01:32:31 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_redircmd(int fd, char **cmd, char *command, t_struct *st)
{
	if (st->redirection == SIMPLERED || st->redirection == DOUBLERED) // != 0 ?
	{
		if (st->redirection == DOUBLERED)
			fd = open(st->newfd, O_CREAT | O_RDWR | O_APPEND, 0640);
		else
			fd = open(st->newfd, O_WRONLY | O_TRUNC | O_CREAT | O_EXCL |
				S_IRGRP | S_IWGRP | S_IWUSR);
		close(1);
		dup(fd);
		close(fd);
		free(st->newfd);
		if (execve(cmd[0], cmd, st->copyenvp) == -1)
		{
			dup2(2, 1);
			ft_printf("minishell: %s : command not found\n", command);
		}
	}
	else
	{
		if (execve(cmd[0], cmd, st->copyenvp) == -1)
		{
			ft_printf("minishell: %s : command not found\n", command);
			ft_freetab(cmd);
		}
	}
}

void	ft_execcmd(t_struct *st, char *command, char **cmd)
{
	pid_t	pid;
	int		status;
	int		fd;

	pid = fork();
	status = 0;
	fd = 0;
	if (pid == -1)
		ft_printf("minishell: fork error\n");
	else if (pid > 0)
	// parent process
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			st->exitstatus = WEXITSTATUS(status);
		kill(pid, SIGTERM);
	}
	else
	// child process
	{
		ft_redircmd(fd, cmd, command, st);
		exit(127);
	}
}
