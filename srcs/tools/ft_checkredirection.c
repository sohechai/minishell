/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkredirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:26:54 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/12 16:20:32 by sohechai         ###   ########lyon.fr   */
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
		st->redirection = DOUBLERED;
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
			while (cmd[i] == '>')
				i++;
			return (i);
		}
		else if (cmd[i] == '<')
		{
			i++;
			st->leftredir = 1;
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

int			ft_strlenuntilredir(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>')
			return (i);
		else if (str[i] == '<')
			return (i);
		i++;
	}
	return (i);
}
