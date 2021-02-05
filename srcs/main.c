/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:29:15 by tcurinie          #+#    #+#             */
/*   Updated: 2021/02/06 00:19:03 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO list :
// - Export ok
// - cd ok
// - pwd ok
// - env ok
// - ; ok
// - ' et " "
// - clean le fichier ft_execbuiltin
// - Echo : gestion des commentaires #, et $ avec ft_getenv
// - Remplacer tous les printf pas des dprintf
// - ft_exit : probleme la cmd doit etre executé 2 fois avant de quitter ..
// - mise a jour header de aurelien
// - <, > et “>>”
// - Pipes |
// - $?
// - ctrl-C, ctrl-D et ctrl-\


// int			ft_allocbuffer(char *buffer, char *cwd, size_t buf_size)
// {
// 	buffer = (char *)ft_calloc(sizeof(char), buf_size);
// 	if (buffer == NULL)
// 	{
// 		ft_printf("malloc failure");
// 		return (EXIT_FAILURE);
// 	}
// 	ft_printf("\033[0;34mMinishell$> \e[00m");
// 	getcwd(cwd, sizeof(cwd));
// 	return (0);
// }

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

void			ft_copyenvp(char **envp, t_struct *st)
{
	int		i;
	int		len;

	i = 0;
	len = ft_countenv(envp);
	if(!(st->copyenvp = ft_calloc(sizeof(char*), (len + 1))))
		ft_printf("failed allocate memory to envp\n");
	while (envp[i])
	{
		st->copyenvp[i] = strdup(envp[i]);
		i++;
	}
	st->copyenvp[i] = NULL;
}

int     	main(int argc, char **argv, char **envp)
{
	t_struct	*st;
	t_mini		*mi;
	if (!(st = ft_initstruct()) || !(mi = ft_initmini()))
	{
		ft_printf("failed allocate memory to structure\n");
		return (0);
	}
	if (argc < 1)
		return (-1);
	(void)argv;
	ft_copyenvp(envp, st);
	ft_printf("\033[0;34mMinishell$> \033[0m");
	while (get_next_line(1, &mi->line) > 0)
	{
		if (parseloop(mi))
			execloop(mi, st, envp);
		ft_reset_mi(mi);
		ft_printf("\033[0;34mMinishell$> \033[0m");
	}
}
