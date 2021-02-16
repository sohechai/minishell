/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:29:15 by tcurinie          #+#    #+#             */
/*   Updated: 2021/02/16 12:23:37 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO list :
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
// - rajouter return (130) pour
// - Echo : gestion des commentaires #, et $ avec ft_getenv
// - Echo : pour $? -> if (echo $?) printf(st->exitstatus); (retour erreur des commandes)
// - Remplacer tous les printf pas des dprintf
// - mise a jour header de aurelien
// - <, > et “>>”
// - Pipes |
// - ctrl-\ -> ne quitte pas mais affiche un caractere


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
	else if (ft_parsing(mi, 0))
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

//TODO check si j'utilise st->sortenv

void			ft_copysortenvp(char **envp, t_struct *st)
{
	int		i;
	int		len;

	i = 0;
	len = ft_countenv(envp);
	if(!(st->sortenv = ft_calloc(sizeof(char*), (len + 1))))
		ft_printf("failed allocate memory to envp\n");
	while (envp[i])
	{
		st->sortenv[i] = ft_strdup(envp[i]);
		i++;
	}
	st->sortenv[i] = NULL;
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
		st->copyenvp[i] = ft_strdup(envp[i]);
		i++;
	}
	st->copyenvp[i] = NULL;
	i = 0;
}

void ft_sigint()
{
	ft_printf("\n");
	ft_printf("\033[0;34mMinishell$> \033[0m");
}

void ft_sigquit()
{
	//ft_printf(" ");
	(void) signal(SIGQUIT, SIG_IGN);
}

int     	main(int argc, char **argv, char **envp)
{
	t_struct	*st;
	t_mini		*mi;
	if (!(st = ft_initstruct()) || !(mi = ft_initmini()))
	{
		ft_printf("failed allocate memory to structure\n");
		return (EXIT_FAILURE);
	}
	if (argc < 1)
		return (-1);
	(void)argv;
	ft_copyenvp(envp, st);
	ft_printf("\033[0;34mMinishell$> \033[0m");
	(void) signal(SIGINT, ft_sigint);
	(void) signal(SIGQUIT, ft_sigquit);
	while (get_next_line(1, &mi->line) > 0)
	{
		if (parseloop(mi))
			execloop(mi, st, envp);
		ft_reset_mi(mi);
		ft_printf("\033[0;34mMinishell$> \033[0m");
	}
	ft_printf("exit\n");
	return (0);
}
