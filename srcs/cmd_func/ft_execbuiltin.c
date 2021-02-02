/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execbuiltin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:25:24 by sohechai          #+#    #+#             */
/*   Updated: 2021/02/01 22:24:42 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** TODO exit cd pwd
** a ajouter au master : struct t_env avec char **env qui recupere toutes les
** variables d'environnement, fichier ft_getenv.c, ft_initstruct.c
** make -C lib/libft && gcc -Wall -Wextra -Werror -L lib/libft -lft
** srcs/cmd_func/ft_execbuiltin.c && ./a.out
** clean = make fclean lib/libft && rm ./a.out
*/

void		ft_freestruct(t_env *st)
{
	if (st->env)
		free(st->env);
	if (st->oldpwd)
		free(st->oldpwd);
	if (st)
		free(st);
}

void	ft_freetab(char **tab)
{
	int		i;

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

void	ft_getabsolutepath(char **cmd, t_env *st)
{
	char	*path = strdup(ft_getenv(st->env, "PATH"));
	char	*bin = NULL;
	char	**path_split = NULL;
	int		i;

	i = 0;
	if (path == NULL)
		path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
	if (cmd[0][0] != '/' && strncmp(cmd[0], "./", 2) != 0)
	{
		path_split = ft_splits(path, ":");
		free(path);
		path = NULL;
		while (path_split[i])
		{
			bin = (char *)calloc(sizeof(char), (ft_strlen(path_split[i]) + 1 + ft_strlen(cmd[0]) + 1));
			if (bin == NULL)
				break ;
			ft_strcat(bin, path_split[i]);
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

void		ft_builtinpwd(void)
{
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_printf("%s\n", cwd);
	}
	else
	{
		perror("getcwd()"); // TODO fonction non autorisée à modifier
	}
}

void		ft_builtincd(char *path)
{
	if (chdir(path) == -1)
	{
		ft_printf("cd: %s: No such file or directory\n", path);
	}
}

void	ft_execcmd(char **cmd)
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
			ft_printf("command not found\n"); // TODO printf le nom de la commande
		exit(EXIT_FAILURE);
	}
}

int		ft_is_built_in(char *cmd)
{
	int         i;
	const char	*built_in[] = {"pwd", "cd", "exit", NULL};

	i = 0;
	while (built_in[i])
	{
		if (!ft_strcmp((char*)built_in[i], cmd))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exec_built_in(char **built_in, t_env *st)
{
	if (!ft_strcmp(built_in[0], "pwd"))
		ft_builtinpwd();
	else if (!ft_strcmp(built_in[0], "cd") && built_in[1] == 0)
	{
		ft_builtincd(ft_getenv(st->env, "HOME"));
	}
	else if (!ft_strcmp(built_in[0], "cd"))
	{
		if (ft_strcmp(built_in[1], "~") == 0)
			built_in[1] = ft_strdup(ft_getenv(st->env, "HOME"));
		else if (ft_strcmp(built_in[1], "-") == 0)
		{
			ft_printf("%s\n", st->oldpwd);
			built_in[1] = ft_strdup(st->oldpwd);
		}
		ft_builtincd(built_in[1]);
	}
}
