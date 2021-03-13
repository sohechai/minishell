/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execbuiltin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:25:24 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/13 18:04:42 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_simpleanddoublered(t_struct *st, int fd, char **cmd, char *command)
{
	if (st->redirection == DOUBLERED)
		fd = open(st->newfd, O_CREAT | O_RDWR | O_APPEND, 0640);
	else
		fd = open(st->newfd, O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	close(1);
	dup(fd);
	close(fd);
	if (execve(cmd[0], cmd, st->copyenvp) == -1)
	{
		dup2(2, 1);
		ft_printf("minishell: %s : command not found\n", command);
	}
}

void	ft_redircmd(int fd, char **cmd, char *command, t_struct *st)
{
	if (st->redirection == SIMPLERED || st->redirection == DOUBLERED)
		ft_simpleanddoublered(st, fd, cmd, command);
	else if (st->leftredir == 1)
	{
		fd = open(st->newfd, O_RDONLY, 0);
		dup2(fd, STDIN_FILENO);
		close(fd);
		if (execve(cmd[0], cmd, st->copyenvp) == -1)
			ft_printf("minishell: %s : command not found\n", command);
	}
	else
	{
		if (execve(cmd[0], cmd, st->copyenvp) == -1)
			ft_printf("minishell: %s : command not found\n", command);
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
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exitstatus = WEXITSTATUS(status);
		kill(pid, SIGTERM);
	}
	else
	{
		ft_redircmd(fd, cmd, command, st);
		exit(127);
	}
}
