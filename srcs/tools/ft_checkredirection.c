/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkredirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:26:54 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/16 21:11:21 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	// printf("redirection = %d\n", st->redirection);
	// printf("file = [%s]\n", ft_strdup(cmd + ft_indexuntilfile(cmd, st)));
	return (EXIT_SUCCESS);
}
