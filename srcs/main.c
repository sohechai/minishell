/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:29:15 by tcurinie          #+#    #+#             */
/*   Updated: 2021/02/03 20:48:42 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO list :
// echo a ajouter car ne gere pas les commentaires #
// dprintf a ajouter et remplacer tous les printf pas des dprintf
// unset et export => une fois done cd - fonctionnera

static void		ft_exit()
{
	// pid_t pid;
	ft_printf("exit\n");
	// ft_freetab(cmd);
	// ft_freestruct(st);
	// pid = getpid();
	// kill(pid, SIGQUIT);
	// TODO faire fonction ft_exit qui free proprement tout ce qui a ete alloué
	exit(EXIT_SUCCESS);
}

int			ft_allocbuffer(char *buffer, char *cwd, t_struct *st, size_t buf_size)
{
	buffer = (char *)ft_calloc(sizeof(char), buf_size);
	if (buffer == NULL)
	{
		ft_printf("malloc failure"); // TODO fonction non autorisée à modifier / recoder perror avec errno
		return (EXIT_FAILURE);
	}
	ft_printf("\033[0;34mMinishell$> \e[00m");
	getcwd(cwd, sizeof(cwd));
	st->oldpwd = cwd;
	return (0);
}

int				ft_simplecmd(t_struct *st)
{
	char	**cmd;
	char    *buffer = NULL;
	size_t  buf_size = 5;
	char	cwd[PATH_MAX];

	cmd = NULL;
	ft_allocbuffer(buffer, cwd, st, buf_size);
	while (get_next_line(0, &buffer))
	{
		cmd = ft_strtok(buffer, " \n\t");
		if (cmd[0] == NULL)
			ft_printf("");
		else if (ft_is_built_in(cmd[0]) == false)
		{
			ft_getabsolutepath(cmd, st);
			ft_execcmd(cmd);
		}
		else if (!ft_strcmp(cmd[0], "exit"))
			ft_exit();
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
	t_struct	*st;

	if (!(st = ft_initstruct()))
	{
		printf("failed allocate memory to structure\n");
		return (0);
	}
	if (argc < 1)
		return (-1);
	(void)argv;
	st->copyenvp = ft_copyenv(envp);
	// if (parsing == pipe ft_parsing == 1 -> pipe ok ft_cmdwithpipe 0 -> no pipe ft_simplecmd(st);
	ft_simplecmd(st);
}
