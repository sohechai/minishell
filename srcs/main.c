/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:29:15 by tcurinie          #+#    #+#             */
/*   Updated: 2021/02/04 15:29:31 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO list :
// echo a ajouter car ne gere pas les commentaires #
// dprintf a ajouter et remplacer tous les printf pas des dprintf
// unset et export => une fois done cd - fonctionnera

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

int			parseloop(t_mini *mi)
{
	if (mi->line[0] == '\0' || !ft_check_character(mi))
	{
		return (0);
	}
	else if (ft_parsing(mi))
	{
		return (1);
	}
	return (1);
}

void		execloop(t_mini *mi, t_struct *st, char **envp)
{
	size_t		n;

	n = 0;
	while (n < mi->semi)
	{
		if (mi->tab_pipe[n] == 0)
		{
			ft_simplecmd(st, mi, envp, n);
			n++;
		}
//		else if (mi->tab_pipe[n] == 1)
//		{
//			n = pipecmd(st, mi, envp, n);
//		}
	}
}

int     	main(int argc, char **argv, char **envp)
{
	t_struct	*st;
	t_mini		*mi;
	if (!(st = ft_initstruct()) || !(mi = ft_initmini()))
	{
		printf("failed allocate memory to structure\n");
		return (0);
	}
	if (argc < 1)
		return (-1);
	(void)argv;
	st->copyenvp = envp;
	ft_printf("\033[0;34mMinishell$> \033[0m");
	while (get_next_line(1, &mi->line) > 0)
	{
		if (parseloop(mi))
			execloop(mi, st, envp);
		ft_reset_mi(mi);
		ft_printf("\033[0;34mMinishell$> \033[0m");
	}
}
