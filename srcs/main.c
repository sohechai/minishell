/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:29:15 by tcurinie          #+#    #+#             */
/*   Updated: 2021/02/01 16:59:37 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		ft_exit(char **cmd, t_env *st)
{
	pid_t pid;
	ft_printf("exit\n");
	ft_freetab(cmd);
	ft_freestruct(st);
	pid = getpid();
	kill(pid, SIGQUIT);
	// TODO faire fonction ft_exit qui free proprement tout ce qui a ete alloué
	exit(EXIT_SUCCESS);
}

static int		ft_allocbuffer(char *buffer, char *cwd, t_env *st, size_t buf_size)
{
	buffer = (char *)calloc(sizeof(char), buf_size);
	if (buffer == NULL)
	{
		perror("Malloc failure"); // TODO fonction non autorisée à modifier / recoder perror avec errno
		return (EXIT_FAILURE);
	}
	ft_printf("\033[0;34mMinishell$> \e[00m");
	getcwd(cwd, sizeof(cwd));
	st->oldpwd = cwd;
	return (0);
}

int				ft_simplecmd(t_env *st)
{
	char	**cmd = NULL;
	char    *buffer = NULL;
	size_t  buf_size = 2048;
	char	cwd[PATH_MAX];
	ft_allocbuffer(buffer, cwd, st, buf_size);
	while (getline(&buffer, &buf_size, stdin) > 0)
	{
		cmd = ft_splits(buffer, " \n\t");
		if (cmd[0] == NULL)
			ft_printf("");
		else if (ft_is_built_in(cmd[0]) == false)
		{
			ft_getabsolutepath(cmd, st);
			ft_execcmd(cmd);
		}
		else if (!ft_strcmp(cmd[0], "exit"))
			ft_exit(cmd, st);
		else
			ft_exec_built_in(cmd, st);
		ft_printf("\033[0;34mMinishell$> \e[00m");
		ft_freetab(cmd);
	}
	ft_printf("exit\n");
	free(buffer);
	return (EXIT_SUCCESS);
}

int     	main(int argc, char **argv, char **envp)
{
	t_env	*st;
	if (!(st = ft_initstruct()))
	{
		printf("failed allocate memory to structure\n");
		return (0);
	}
	if (argc < 1)
		return (-1);
	(void)argv;
	st->env = envp;
	// ft_parsing == 1 -> pipe ok ft_cmdwithpipe 0 -> no pipe ft_simplecmd(st);
	ft_simplecmd(st);
}
