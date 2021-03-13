/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subredir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 13:08:29 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/13 17:35:09 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				ft_subredirr(char *redir)
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
	ft_freetab(str);
	return (i);
}

char			*ft_subwithoutspace(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i])
	{
		if (src[i] == '>' || src[i] == '<')
			break ;
		i++;
	}
	dest = ft_substr(src, 0, i);
	return (dest);
}

static char		*sub_loop(char **cmd, char *dest)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		cmd[i] = ft_strfjoin(cmd[i], " ", 1);
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
	return (dest);
}

char			*ft_subredir(char *src, t_struct *st)
{
	char	**cmd;
	char	*dest;
	char	*tmp;

	if (!ft_strchr(src, ' ') || st->pipecmd == 1)
	{
		if (st->pipecmd == 1)
		{
			src = ft_strtrim(src, " ");
		}
		return (ft_subwithoutspace(src));
	}
	cmd = ft_strtokk(src, " ");
	dest = ft_strdup("");
	dest = sub_loop(cmd, dest);
	ft_freetab(cmd);
	tmp = ft_strtrim(dest, " ");
	ft_delete(&dest);
	dest = ft_strdup(tmp);
	ft_delete(&tmp);
	return (dest);
}
