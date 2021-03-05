/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:29:15 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/05 23:29:04 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int exitstatus;
// OK :
// - Export ok
// - Unset ok
// - cd ok
// - pwd ok
// - env ok
// - ; ok
// - exit ok
// - ctrl-D ok
// - ctrl-C ok
// - ' et " " ok
// - export $var ok
// - <, > et >> ok
// - pipe okkkkkkkkkkkdlkfjgj

// TODO list :
// - abc def -> minishell: def : command not found leak de def
// - pb redirection pipe mm fichier
// - leak dans ft_exit ?
// - ls < text.txt < text2.txt -> minishell: syntax error near unexpected token '<'



int			parseloop(t_struct *st)
{
	if (st->line[0] == '\0' || !ft_check_character(st))
		return (0);
	if (!ft_parsing(st, 0))
		return (0);
	return (1);
}

int			execloop(t_struct *st)
{
	size_t		n;
	char *tmp;

	n = 0;
	while (n < st->semi)
	{
		if (st->tab_pipe[n] == 0)
		{
			ft_redirection(st->tab_arg[n], st);
			if (st->redirection == 0)
				ft_simplecmd(st, n);
			else
			{
				if (st->stop == 0)
				{
					tmp = ft_strdup(st->tab_arg[n]);
					free(st->tab_arg[n]);
					st->tab_arg[n] = ft_substr(tmp, 0,
								ft_strlenuntilredir(tmp));
					free(tmp);
					ft_simplecmd(st, n);
				}
			}
		}
		else if (st->tab_pipe[n] == 1)
			ft_pipecmd(st, n);
		n++;
	}
	return (EXIT_SUCCESS);
}

void		ft_copyenvp(char **envp, t_struct *st)
{
	int		i;
	int		len;

	i = 0;
	len = ft_countenv(envp);
	if (!(st->copyenvp = ft_calloc(sizeof(char*), (len + 1))))
		ft_printf("failed allocate memory to envp\n");
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "OLDPWD", 6))
			st->copyenvp[i] = ft_strdup("OLDPWD");
		else
			st->copyenvp[i] = ft_strdup(envp[i]);
		i++;
	}
	st->copyenvp[i] = NULL;
	i = 0;
}

int			main(int argc, char **argv, char **envp)
{
	t_struct	*st;
	exitstatus = 0;
	if (!(st = ft_initstruct()))
	{
		ft_printf("failed allocate memory to structure\n");
		return (EXIT_FAILURE);
	}
	if (argc != 1)
	{
		ft_printf("too much argument, enter './minishell' to execute\n");
		return (-1);
	}
	(void)argv;
	ft_copyenvp(envp, st);
	ft_printf("\033[0;34mMinishell$> \033[0m");
	signal(SIGINT, ft_handlesignal);
	signal(SIGQUIT, ft_handlesignal);
	while (get_next_line(1, &st->line) > 0)
	{
		if (parseloop(st))
		{
			execloop(st);
			ft_reset_mi(st);
		}
		ft_delete(&st->line);
		ft_printf("\033[0;34mMinishell$> \033[0m");
	}
	// ft_freetab(st->copyenvp);
	// free(st);
	return (0);
}
