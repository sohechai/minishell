/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subredir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 13:08:29 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/13 15:49:56 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_subredirr(char *redir)
{
	int		i;
	char	**str;

	i = 0;
	if (!ft_strcmp(redir, ">") || !ft_strcmp(redir, "<"))
		return (-1);
	else
		str = ft_strtokk(redir, "> <");
	while (str[i])
		i++;
	return (i);
}

char		*ft_subwithoutspace(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	while(src[i])
	{
		if (src[i] == '>' || src[i] == '<')
			break ;
		i++;
	}
	dest = ft_substr(src, 0, i);
	return (dest);
}

char		*ft_subredir(char *src)
{
	int		i;
	char	**cmd;
	char	*dest;

	i = 0;
	if (!ft_strchr(src, ' '))
		return (ft_subwithoutspace(src));
	cmd = ft_strtokk(src, " ");
	dest = ft_strdup("");
	while (cmd[i])
	{
		cmd[i] = ft_strjoin(cmd[i], " ");
		if (ft_strchr(cmd[i], '>') || ft_strchr(cmd[i], '<'))
		{
			if (ft_subredirr(cmd[i]) == 0 && cmd[i + 1] != NULL)
				i += 2;
			else
				i++;
		}
		else
		{
			dest = ft_strfjoin(dest, cmd[i], 1);
			i++;
		}
	}
	ft_freetab(cmd);
	dest = ft_strtrim(dest, " ");
	return (dest);
}
