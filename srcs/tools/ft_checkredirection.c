/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkredirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:26:54 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/27 20:18:51 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_lenoffile(char *cmd)
{
	int		count;
	int		len;

	count = 0;
	len = ft_strlen(cmd);
	while (len != 0)
	{
		if (cmd[len] == '/')
			return (count - 1);
		len--;
		count++;
	}
	return (-1);
}

int			ft_sortredirection(char *cmd, int i, t_struct *st)
{
	if (cmd[i + 1] == '>')
	{
		// if (cmd[i + 2] == '>')
		// {
		// 	printf("erreur de syntaxe près du symbole inattendu « >> »\n");
		// 	st->redirection = 0;
		// 	return (0);
		// }
		st->redirection = DOUBLERED;
	}
	else
		st->redirection = SIMPLERED;
	return (1);
}

int			ft_indexuntilfile(char *cmd, t_struct *st)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>')
		{
			ft_sortredirection(cmd, i, st);
			while (cmd[i] == '>' || cmd[i] == ' ')
				i++;
			return (i);
		}
		else if (cmd[i] == '<')
		{
			i++;
			st->redirection = LEFTRED;
			while (cmd[i] == ' ')
				i++;
			return (i);
		}
		i++;
	}
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
		if (str[i] == '<')
			return (i);
		i++;
	}
	return (i);
}

int		ft_redirection(char *cmd, t_struct *st)
{
	int			i;
	int			fd;

	i = 0;
	if (ft_indexuntilfile(cmd, st) == 0)
		return (0);
	if (st->redirection != 0)
	{
		if (ft_lenoffile(cmd) != -1)
		{
			if (ft_checkfile(cmd, st) == 0)
				return (0);
		}
		st->newfd = ft_strdup(cmd + ft_indexuntilfile(cmd, st));
		st->files = ft_strtokk(st->newfd, " ><|");
		while (st->files[i] != NULL)
		{
			if (st->files[i + 1] != NULL)
				fd = open(st->files[i], O_CREAT | O_RDWR | O_APPEND, 0640);
			i++;
		}
		if (i > 1)
		{
			free(st->newfd);
			st->newfd = ft_strdup(st->files[i - 1]);
		}
	}
	return (EXIT_SUCCESS);
}
