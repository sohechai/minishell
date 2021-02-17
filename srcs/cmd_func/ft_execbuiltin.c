/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execbuiltin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:25:24 by sohechai          #+#    #+#             */
/*   Updated: 2021/02/17 21:37:07 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pathsplit(char **cmd, char **path_split, char *path, char *bin)
{
	int		id;
	int		i;

	path_split = ft_split(path, ':');
	free(path);
	path = NULL;
	i = 0;
	while (path_split[i])
	{
		bin = (char *)ft_calloc(sizeof(char), (ft_strlen(path_split[i]) + \
		ft_strlen(cmd[0]) + 2));
		if (bin == NULL)
			break ;
		ft_strcat(bin, path_split[i]);
		ft_strcat(bin, "/");
		ft_strcat(bin, cmd[0]);
		id = open(bin, O_RDONLY);
		if (id > 0)
			break ;
		free(bin);
		bin = NULL;
		i++;
	}
	ft_freetab(path_split);
	free(cmd[0]);
	cmd[0] = bin;
}

void	ft_getabsolutepath(char **cmd, t_struct *st)
{
	char	*path;
	char	*bin;
	char	**path_split;
	int		i;

	path = ft_strdup(ft_getenv(st->copyenvp, "PATH"));
	bin = NULL;
	path_split = NULL;
	i = 0;
	if (path == NULL)
		path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
	if (cmd[0][0] != '/' && strncmp(cmd[0], "./", 2) != 0)
	{
		ft_pathsplit(cmd, path_split, path, bin);
	}
	else
	{
		free(path);
		path = NULL;
	}
}

void	ft_execcmd(t_struct *st, char *command, char **cmd)
{
	pid_t	pid;
	int		status;
	int		fd;

	pid = fork();
	status = 0;
	if (pid == -1)
		ft_printf("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			st->exitstatus = WEXITSTATUS(status);
		kill(pid, SIGTERM);
	}
	else
	{
		if ((st->redirection == SIMPLERED || st->redirection == DOUBLERED))
		{
			if (st->redirection == DOUBLERED)
				fd = open(st->newfd, O_CREAT | O_RDWR | O_APPEND, 0640);
			else
				fd = open(st->newfd, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR |
					S_IRGRP | S_IWGRP | S_IWUSR);
			close(1);
			dup(fd);
			close(fd);
			if (execve(cmd[0], cmd, NULL) == -1)
			{
				dup2(2, 1);
				ft_printf("%s : command not found\n", command);
			}
		}
		else if (st->redirection == 0)
		{
			if (execve(cmd[0], cmd, NULL) == -1)
			{
				ft_printf("%s : command not found\n", command);
			}
		}
		exit(127);
	}
}

int		ft_is_built_in(char *cmd)
{
	int			i;
	const char	*built_in[] = {"pwd", "cd", "env", "echo", "export", "unset", NULL};

	i = 0;
	while (built_in[i])
	{
		if (!ft_strcmp((char*)built_in[i], cmd))
			return (1);
		i++;
	}
	return (0);
}

int		ft_exec_built_in(t_mini *mi, char **built_in, t_struct *st, size_t n)
{
	if (!ft_strcmp(built_in[0], "pwd"))
		ft_builtinpwd(st);
	else if (!ft_strcmp(built_in[0], "cd") && built_in[1] == 0)
	{
		ft_saveoldpwd(st);
		ft_builtincd(ft_getenv(st->copyenvp, "HOME"), st);
	}
	else if (!ft_strcmp(built_in[0], "cd"))
		ft_cdwithargs(built_in, st);
	else if (!ft_strcmp(built_in[0], "env") && built_in[1] == NULL)
		ft_env(st->copyenvp, st);
	else if (!ft_strcmp(built_in[0], "env") && built_in[1] != NULL)
	{
		ft_printf("env: %s : No such file or directory\n", built_in[1]);
		return (st->exitstatus = 127);
	}
	else if (!ft_strcmp(built_in[0], "export") && built_in[1] == 0)
		ft_printsortenv(st);
	else if (!ft_strcmp(built_in[0], "export"))
		ft_exportloop(built_in, st);
	else if (!ft_strcmp(built_in[0], "unset") && built_in[1] != 0)
		ft_unsetloop(built_in, st);
	else if (!ft_strcmp(built_in[0], "echo"))
		ft_echo(mi, n, st);
	return (EXIT_SUCCESS);
}
