/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execbuiltin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:25:24 by sohechai          #+#    #+#             */
/*   Updated: 2021/01/22 15:08:29 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <limits.h>
#include <signal.h>

// make -C lib/libft && gcc -Wall -Wextra -Werror -L lib/libft -lft srcs/cmd_func/ft_execbuiltin.c && ./a.out

static char	**split(char *raw_cmd, char *limit)
{
	char	*ptr = NULL;
	char	**cmd = NULL;
	size_t	i = 0;

	ptr = strtok(raw_cmd, limit);
	while (ptr)
	{
		cmd = (char **)realloc(cmd, ((i + 1) * sizeof(char *)));
		cmd[i] = ft_strdup(ptr);
		ptr = strtok(NULL, limit); // TODO ft strtok
		++i;
	}
	cmd = (char **)realloc(cmd, ((i + 1) * sizeof(char *)));
	cmd[i] = NULL;
	return (cmd);
}

static void	ft_freetab(char **tab)
{
	int     i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

static void	ft_getabsolutepath(char **cmd)
{
	char	*path = strdup(getenv("PATH"));
	char	*bin = NULL;
	char	**path_split = NULL;
	int		i;

	i = 0;
	if (path == NULL)
		path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
	if (cmd[0][0] != '/' && strncmp(cmd[0], "./", 2) != 0) 
	{
		path_split = split(path, ":");
		free(path);
		path = NULL;
		while (path_split[i]) 
		{
			bin = (char *)calloc(sizeof(char), (strlen(path_split[i]) + 1 + strlen(cmd[0]) + 1));
			if (bin == NULL)
				break ;
			ft_strcat(bin, path_split[i]); // TODO add ft_strcat
			ft_strcat(bin, "/");
			ft_strcat(bin, cmd[0]);
			if (access(bin, F_OK) == 0)
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

void	ft_builtinpwd(void)
{
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		   printf("%s\n", cwd);
	}
	else
	{
		perror("getcwd()");
	}
}

void	ft_builtincd(char *path)
{
	if (chdir(path) == -1)
	{
		ft_printf("chdir = -1\n");
	}
}

static void	exec_cmd(char **cmd)
{
	pid_t	pid = 0;
	int		status = 0;

	pid = fork();
	if (pid == -1)
		perror("fork"); // TODO fonction non autorisée à modifier
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(cmd[0], cmd, NULL) == -1)
			perror("shell"); // TODO fonction non autorisée à modifier
		exit(EXIT_FAILURE);
	}
}

static int	ft_is_built_in(char *cmd)
{
	int         i;
	const char	*built_in[] = {"pwd", "cd", "exit", NULL};

	i = 0;
	while (built_in[i])
	{
		if (!ft_strcmp(built_in[i], cmd))
			return (1);
		i++;
	}
	return (0);
}

static void	ft_exec_built_in(char **built_in)
{
	if (!ft_strcmp(built_in[0], "pwd"))
		ft_builtinpwd();
	else if (!ft_strcmp(built_in[0], "cd"))
	{
		if (ft_strcmp(built_in[1], "~") == 0)
			built_in[1] = ft_strdup("/Users/sohechai");
		ft_builtincd(built_in[1]);
	}
	else if (!ft_strcmp(built_in[0], "exit"))
	{
		ft_printf("exit\n");
		exit(EXIT_SUCCESS);
	}
}

int     main(void)
{
	char    *buffer = NULL;
	size_t  buf_size = 2048;
	char	**cmd = NULL;

	buffer = (char *)calloc(sizeof(char), buf_size);
	if (buffer == NULL)
	{
		perror("Malloc failure"); // TODO fonction non autorisée à modifier
		return (EXIT_FAILURE);
	}
	ft_printf("$> ");
	while (getline(&buffer, &buf_size, stdin) > 0)
	{
		cmd = split(buffer, " \n\t");
		if (cmd[0] == NULL)
			ft_printf(""); // TODO ft_printf
		else if (ft_is_built_in(cmd[0]) == false)
		{
			ft_getabsolutepath(cmd);
			exec_cmd(cmd);
		}
		else
			ft_exec_built_in(cmd);
		ft_printf("$> ");
		ft_freetab(cmd);
	}
	ft_printf("exit\n");
	free(buffer);
}
