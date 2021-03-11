/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkredirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:26:54 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/12 00:39:55 by sofiahechai      ###   ########lyon.fr   */
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

char		*ft_subredir(char *src)
{
	int		i;
	int		j;
	int 	start;
	int		end;
	char	*dest;

	i = 0;
	j = 0;
	end = ft_strlen(src);
	while (src[i])
	{
		if (src[i] == '>' || src[i] == '<')
			break ;
		i++;
	}
	start = i;
	while(end > 0)
	{
		if (src[end] == ' ')
		{
			while (src[end] == ' ')
				end--;
			if (src[end] == '>' || src[end] == '<')
			{
				end = 0;
				break ;
			}
			else
				break ;
		}
		end --;
	}
	if (!(dest = malloc(sizeof(char) * (start + end) + 1)))
		return (NULL);
	i = 0;
	start --;
	while (i != start)
		dest[j++] = src[i++];
	while (src[end] && end != 0)
		dest[j++] = src[++end];
	dest[j] = '\0';
	return (dest);
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
