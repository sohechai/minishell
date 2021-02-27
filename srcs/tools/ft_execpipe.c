/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execpipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:33:59 by sohechai          #+#    #+#             */
/*   Updated: 2021/02/27 16:16:14 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// https://stackoverflow.com/questions/8082932/connecting-n-cmd-with-pipes-in-a-shell
// https://stackoverflow.com/questions/26788603/simple-shell-with-pipe-function
// https://forum.hardware.fr/hfr/Programmation/C/implementation-shell-pipe-sujet_50490_1.htm
// https://stackoverflow.com/questions/35545785/c-program-to-execute-shell-piping-and-redirection
// https://stackoverflow.com/questions/12679075/almost-perfect-c-shell-piping
// https://stackoverflow.com/questions/60804552/pipe-two-or-more-shell-cmd-in-c-using-a-loop


// int		ft_lenoftab(char **str)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (str[i][j] != NULL)
// 	{
// 		printf("cmd = [%s]\n", str[i]);
// 		i++;
// 	}
// 	printf("i = %d\n", i);
// 	return (i);
// }

int		ft_exec_pipe_built_in(t_mini *mi, char **built_in, t_struct *st)
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
		ft_echo(mi, built_in);
	return (EXIT_SUCCESS);
}

void		ft_execpipe(char *cmd, t_struct *st)
{
	char	**parsecmd;
	char	**command;
	int		index;
    pid_t	pid;
	int		pipefd[2];
	int		fdinput = 0;

	index = 0;
	command = ft_strtokk(cmd, "|");
    while(command[index] != NULL)
	{
		parsecmd = ft_strtokk(command[index], " \n\t");
		ft_getabsolutepath(parsecmd, st);
		pipe(pipefd);
		if ((pid = fork()) == -1)
		{
			ft_printf("fork error\n");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0) // child process
		{
			dup2(fdinput, 0); // change input from last one
			if ((command[index + 1]) != NULL)
				dup2(pipefd[1], 1);
			close(pipefd[0]);
			// if (ft_is_built_in(command[index]) == false)
			// {
			// 	printf("not builtin\n");
				ft_execcmd(st, command[index], parsecmd); // fix problem message d'erreur espace etc
			// }
			// else
			// {
			// 	printf("builtin\n");
			// 	ft_exec_built_in(mi, parsecmd, st);
			// }
			// execve(parsecmd[0], parsecmd, NULL);
			// ft_printf("%s : command not found\n", command[index]);
    		exit( EXIT_FAILURE );
		}
		else // parent process
		{
			wait(NULL);
			close(pipefd[1]);
			fdinput = pipefd[0];  // save input for next command
			index++;
		}
    }
}

static size_t	change_loop(t_mini *mi, size_t i, size_t n, char c)
{
	i++;
	while (mi->tab_arg[n][i] && mi->tab_arg[n][i] != c)
	{
		if (ft_strchr(" \t", mi->tab_arg[n][i]))
			mi->tab_arg[n][i] = -8;
		i++;
	}
	return (i);
}

static void		change_space_char(t_mini *mi, size_t i, size_t n)
{
	while (mi->tab_arg[n][i])
	{
		if (mi->tab_arg[n][i] == '"' || mi->tab_arg[n][i] == '\'')
			i = change_loop(mi, i, n, mi->tab_arg[n][i]) + 1;
		else
			i++;
	}
}

int				ft_pipecmd(t_struct *st, t_mini *mi, char **envp, size_t n)
{
	char	**cmd;
	//char	**parsecmd;
	int     i;

	st->copyenvp = envp;
	i = 0;
	change_space_char(mi, 0, n);
	cmd = ft_strtokk(mi->tab_arg[n], " \t\n");
	cmd = rechange_character(cmd, 0, 0);
	cmd = remove_quote(cmd, 0);
	if (cmd[0] == NULL || !cmd[0][0])
		ft_printf("");
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(mi->tab_arg[n], st);
	// else if (ft_is_built_in(cmd[0]) == false)
		ft_execpipe(mi->tab_arg[n], st);
	// else
	// 	ft_exec_built_in(mi, cmd, st);
	ft_free_tab(cmd);
	// 	i++;
	// }
	return (EXIT_SUCCESS);
}
