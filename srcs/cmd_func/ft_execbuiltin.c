/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execbuiltin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:25:24 by sohechai          #+#    #+#             */
/*   Updated: 2021/02/08 17:29:03 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// TODO get absolute path a raccourcir

void	ft_getabsolutepath(char **cmd, t_struct *st)
{
	char	*path = ft_strdup(ft_getenv(st->copyenvp, "PATH"));
	char	*bin = NULL;
	char	**path_split = NULL;
	int		i;
	int 	id;

	i = 0;
	if (path == NULL)
		path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
	if (cmd[0][0] != '/' && strncmp(cmd[0], "./", 2) != 0)
	{
		path_split = ft_split(path, ':');
		free(path);
		path = NULL;
		while (path_split[i])
		{
			bin = (char *)ft_calloc(sizeof(char), (ft_strlen(path_split[i]) + 1 + ft_strlen(cmd[0]) + 1));
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
	else
	{
		free(path);
		path = NULL;
	}
}

void	ft_execcmd(char **cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 0;
	if (pid == -1)
		ft_printf("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(cmd[0], cmd, NULL) == -1)
			ft_printf("command not found\n");
		exit(EXIT_FAILURE);
	}
}

int		ft_is_built_in(char *cmd)
{
	int         i;
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

void		ft_saveoldpwd(t_struct *st)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	getcwd(cwd, sizeof(cwd));
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	ft_exportenv(oldpwd, st);
}

void		ft_savepwd(t_struct *st)
{
	char	cwd[PATH_MAX];
	char	*pwd;
	getcwd(cwd, sizeof(cwd));
	pwd = ft_strjoin("PWD=", cwd);
	ft_exportenv(pwd, st);
}

// TODO execbuiltin a raccourcir

void	ft_exec_built_in(t_mini *mi, char **built_in, t_struct *st, size_t n)
{
	st->i = 1;
	if (!ft_strcmp(built_in[0], "pwd"))
		ft_builtinpwd(st);
	else if (!ft_strcmp(built_in[0], "cd") && built_in[1] == 0)
	{
		ft_saveoldpwd(st);
		ft_builtincd(ft_getenv(st->copyenvp, "HOME"), st);
	}
	else if (!ft_strcmp(built_in[0], "cd"))
	{
		if (ft_strcmp(built_in[1], "~") == 0)
		{
			ft_saveoldpwd(st);
			built_in[1] = ft_strdup(ft_getenv(st->copyenvp, "HOME"));
		}
		else if (ft_strcmp(built_in[1], "-") == 0)
		{
			if (!ft_getenv(st->copyenvp, "OLDPWD"))
				ft_printf("cd: « OLDPWD » non défini");
			else
			{
				ft_printf("%s\n", ft_strdup(ft_getenv(st->copyenvp, "OLDPWD")));
				built_in[1] = ft_strdup(ft_getenv(st->copyenvp, "OLDPWD"));
			}
		}
		ft_saveoldpwd(st);
		ft_builtincd(built_in[1], st);
	}
	else if (!ft_strcmp(built_in[0], "echo"))
		ft_echo(mi, n);
	else if (!ft_strcmp(built_in[0], "env"))
		ft_env(st->copyenvp);
	else if (!ft_strcmp(built_in[0], "export") && built_in[1] == 0)
		ft_printsortenv(st);
	else if (!ft_strcmp(built_in[0], "export"))
	{
		while (built_in[st->i] != NULL)
		{
			ft_exportenv(built_in[st->i], st);
			st->i++;
		}
	}
	else if (!ft_strcmp(built_in[0], "unset") && built_in[1] != 0)
	{
		st->i = 0;
		while (built_in[st->i] != NULL)
		{
			ft_unsetenv(built_in[st->i], st);
			st->i++;
		}
	}
}
