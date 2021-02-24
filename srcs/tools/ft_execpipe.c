/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execpipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:33:59 by sohechai          #+#    #+#             */
/*   Updated: 2021/02/24 17:23:55 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// https://stackoverflow.com/questions/8082932/connecting-n-commands-with-pipes-in-a-shell
// https://stackoverflow.com/questions/26788603/simple-shell-with-pipe-function
// https://forum.hardware.fr/hfr/Programmation/C/implementation-shell-pipe-sujet_50490_1.htm
// https://stackoverflow.com/questions/35545785/c-program-to-execute-shell-piping-and-redirection
// https://stackoverflow.com/questions/12679075/almost-perfect-c-shell-piping
// https://stackoverflow.com/questions/60804552/pipe-two-or-more-shell-commands-in-c-using-a-loop


int		ft_lenoftab(char **str)
{
	int		i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

void		ft_execpipe(char **cmd)
{
	(void)cmd;
	// pid_t		pid;
	// int			status;
	// int 		i;
	// int			j;
	// int			q = 0;
	// int 		in;
	// int			pipefd[2];
	// int			len;

	// i = 0;
	// j = 0;
	// in = 0;
	// pipe(pipefd);
	// pid = fork();
	// len = ft_lenoftab(cmd);
	// while (i < len - 1)
	// {
	// 	if (dup2(pipefd[j + 1], 1) < 0)
	// 	{
	// 		perror("dup2");
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	if (j != 0)
	// 	{
	// 		if (dup2(pipefd[j - 2], 0) < 0)
	// 		{
	// 			perror("dup2");
	// 			exit(EXIT_FAILURE);
	// 		}
	// 		while (q < len)
	// 		{
	// 			close(pipefd[q]);
	// 			q++;
	// 		}
	// 		if (execve(cmd[i], cmd, NULL) == -1)
	// 			ft_printf("%s : command not found\n", cmd[i]);
	// 		j += 2;
	// 		i++;
	// 	}
	// 	while (i < len + 1)
	// 	{
	// 		wait(&status);
	// 	}
	// }
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
	char	**parsecmd;
	int     i;

	st->copyenvp = envp;
	i = 0;
	parsecmd = ft_strtokk(mi->tab_arg[n], "|");
	while (parsecmd[i] != NULL)
	{
		change_space_char(mi, 0, n);
		cmd = ft_strtokk(parsecmd[i], " \t\n");
		cmd = rechange_character(cmd, 0, 0);
		cmd = remove_quote(cmd, 0);
		if (cmd[0] == NULL || !cmd[0][0])
			ft_printf("");
		else if (!ft_strcmp(cmd[0], "exit"))
			ft_exit(mi->tab_arg[n], st);
		else if (ft_is_built_in(cmd[0]) == false)
		{
			st->printerror = ft_strdup(cmd[0]);
			ft_getabsolutepath(cmd, st);
			ft_execpipe(cmd);
			free(st->printerror); // TODO <- free
		}
		else
			ft_exec_built_in(mi, cmd, st);
		ft_free_tab(cmd);
		i++;
	}
	return (EXIT_SUCCESS);
}
