/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:29:15 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/09 12:36:03 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** TODO list :
** - abc def -> minishell: def : command not found leak de def
** - leak ft_exit car double free avec ft_freeloop
*/

int			parseloop(t_struct *st)
{
	if (st->line[0] == '\0' || !ft_check_character(st))
		return (0);
	if (!ft_parsing(st, 0))
		return (0);
	return (1);
}

void		ft_parsecmdwithredir(int n, t_struct *st)
{
	char *tmp;

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

int			execloop(t_struct *st)
{
	size_t		n;

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
				ft_parsecmdwithredir(n, st);
			}
		}
		else if (st->tab_pipe[n] == 1)
			ft_pipecmd(st, n);
		n++;
	}
	return (EXIT_SUCCESS);
}

void		ft_mainloop(t_struct *st)
{
	if (parseloop(st))
	{
		execloop(st);
		ft_reset_mi(st);
	}
	ft_delete(&st->line);
	ft_printf("\033[0;34mMinishell$> \033[0m");
}

int			main(int argc, char **argv, char **envp)
{
	t_struct	*st;

	g_exitstatus = 0;
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
		ft_mainloop(st);
	return (0);
}
