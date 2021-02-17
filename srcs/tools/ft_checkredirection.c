/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkredirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:26:54 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/17 21:19:21 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_redirectbuiltin(t_struct *st)
{
	int		fd;
	st->oldstdout = dup(1);
	if (st->redirection == SIMPLERED || st->redirection == DOUBLERED)
	{
		if (st->redirection == DOUBLERED)
			fd = open(st->newfd, O_CREAT | O_RDWR | O_APPEND, 0640);
		else
			fd = open(st->newfd, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR |
				S_IRGRP | S_IWGRP | S_IWUSR);
		close(1);
		dup(fd);
		close(fd);
	}
}

void		ft_comebacktostdout(t_struct *st)
{
	if (st->redirection == SIMPLERED || st->redirection == DOUBLERED)
	{
		dup2(st->oldstdout, 1);
		close(st->oldstdout);
	}
}

int			ft_indexuntilfile(char *cmd, t_struct *st)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>')
		{
			if (cmd[i + 1] == '>')
			{
				if (cmd[i + 2] == '>')
				{
					printf("erreur de syntaxe près du symbole inattendu « >> »\n");
					return (0);
				}
				else
					st->redirection = DOUBLERED;
			}
			else
				st->redirection = SIMPLERED;
			while (cmd[i] == '>' || cmd[i] == ' ')
				i++;
			return (i);
		}
		i++;
	}
	if (st->redirection != SIMPLERED || st->redirection != DOUBLERED)
		st->redirection = 0;
	return (i);
}

int		ft_strlenuntilredir(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>')
			return (i);
		i++;
	}
	return (i);
}

int		ft_redirection(char *cmd, t_struct *st)
{
	if (ft_indexuntilfile(cmd, st) == 0)
		return (EXIT_FAILURE);
	if (st->redirection != 0)
		st->newfd = ft_strdup(cmd + ft_indexuntilfile(cmd, st));
	return (EXIT_SUCCESS);
}
