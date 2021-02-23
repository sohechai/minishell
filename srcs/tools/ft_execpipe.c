/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execpipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:33:59 by sohechai          #+#    #+#             */
/*   Updated: 2021/02/23 15:56:56 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// https://stackoverflow.com/questions/8082932/connecting-n-commands-with-pipes-in-a-shell
// https://stackoverflow.com/questions/26788603/simple-shell-with-pipe-function

void	ft_execpipe(char *command, char **cmd)
{
    pid_t	pid;
    int		status;
    int		pipefd[2];
    char    *error;

    pipe(pipefd);
    pid = fork();
    status = 0;
    printf("allo\n");
    if (pid == -1) // error
        ft_printf("fork");
    else if (pid > 0) // parent process
    {
        close(pipefd[0]);
        dup2(pipefd[1], 1);
    //close(pipefd[1]);
        if (execve(cmd[0], cmd, NULL) == -1) // run command BEFORE pipe character in userinput
        {
            error = strerror(errno);
            ft_printf("%s: command not found\n", command);
        }
        //exit (127);
    }
    else // child process
    {
        close(pipefd[1]);
        dup2(pipefd[0], 0);
    //close(pipefd[0]);
        if (execve(cmd[0], cmd, NULL) == -1) // run command AFTER pipe character in userinput
        {
            error = strerror(errno);
            ft_printf("%s: command not found\n", command);
        }
       // exit (127);
    }
}

int				ft_pipecmd(t_struct *st, t_mini *mi, char **envp, size_t n)
{
	char	**cmd;

	st->copyenvp = envp;
	if ((ft_strchr(mi->tab_arg[n], '"') || ft_strchr(mi->tab_arg[n], '\'')) &&
		ft_checkquote(mi->tab_arg[n]) == 1)
		cmd = ft_strtokk(mi->tab_arg[n], "\"'");
	else if ((ft_strchr(mi->tab_arg[n], '"') || ft_strchr(mi->tab_arg[n], '\''))
        && ft_checkquote(mi->tab_arg[n]) == -1)
		cmd = ft_strtokk(mi->tab_arg[n], " \n\t\"'");
	else
		cmd = ft_strtokk(mi->tab_arg[n], " \n\t");
	if (cmd[0] == NULL)
		ft_printf("");
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(mi->tab_arg[n], st);
	else if (ft_is_built_in(cmd[0]) == false)
	{
		st->printerror = ft_strdup(cmd[0]);
		ft_getabsolutepath(cmd, st);
		ft_execpipe(st->printerror, cmd);
		//free(st->printerror); TODO <- free
	}
	else
		ft_exec_built_in(mi, cmd, st);
	return (EXIT_SUCCESS);
}
