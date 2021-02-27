/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execpipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:33:59 by sohechai          #+#    #+#             */
/*   Updated: 2021/02/27 21:06:22 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// https://stackoverflow.com/questions/8082932/connecting-n-cmd-with-pipes-in-a-shell
// https://stackoverflow.com/questions/26788603/simple-shell-with-pipe-function
// https://forum.hardware.fr/hfr/Programmation/C/implementation-shell-pipe-sujet_50490_1.htm
// https://stackoverflow.com/questions/35545785/c-program-to-execute-shell-piping-and-redirection
// https://stackoverflow.com/questions/12679075/almost-perfect-c-shell-piping
// https://stackoverflow.com/questions/60804552/pipe-two-or-more-shell-cmd-in-c-using-a-loop


void		ft_execpipe(char *cmd, t_struct *st, t_mini *mi)
{
	char	**parsecmd;
	char	**command;
	int		i;
    pid_t	pid;
	int		pipefd[2];
	int		fdinput = 0;

	i = 0;
	command = ft_strtokk(cmd, "|");
    while(command[i] != NULL)
	{
		ft_redirection(command[i], st);
		if (st->redirection != 0)
			command[i] = ft_substr(command[i], 0, ft_strlenuntilredir(command[i]));
		parsecmd = ft_strtokk(command[i], " \n\t");
		pipe(pipefd);
		if ((pid = fork()) == -1)
		{
			ft_printf("fork error\n");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0) // child process
		{
			dup2(fdinput, STDIN); // change input from last one
			if ((command[i + 1]) != NULL) // lien avec cmd d'apres
				dup2(pipefd[1], STDOUT);
			close(pipefd[0]);
			if (ft_is_built_in(parsecmd[0]) == 0)
			{
				ft_getabsolutepath(parsecmd, st);
				ft_execcmd(st, command[i], parsecmd);
				st->redirection = 0; // TODO utile ?
			} // TODO fix problem message d'erreur espace etc
			else
			{
				ft_exec_built_in(mi, parsecmd, st);
				st->redirection = 0;
			}
    		exit(EXIT_FAILURE);
		}
		else // parent process
		{
			wait(NULL);
			close(pipefd[1]);
			fdinput = pipefd[0];  // save input for next command
			i++;
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
	int     i;

	st->copyenvp = envp;
	i = 0;
	change_space_char(mi, 0, n);
	// cmd = ft_strtokk(mi->tab_arg[n], " \t\n");
	// cmd = rechange_character(cmd, 0, 0);
	// cmd = remove_quote(cmd, 0); // TODO tjrs util ?
	if (cmd[0] == NULL || !cmd[0][0])
		ft_printf("");
	else if (!ft_strcmp(cmd[0], "exit")) // TODO test avec exit
		ft_exit(mi->tab_arg[n], st);
	ft_execpipe(mi->tab_arg[n], st, mi);
	// ft_free_tab(cmd);
	return (EXIT_SUCCESS);
}
