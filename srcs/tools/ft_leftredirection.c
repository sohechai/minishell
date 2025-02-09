/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_leftredirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:16:12 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/12 12:49:51 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char		*ft_subleftfile(char *file, t_struct *st, int count, int start)
{
	int		i;
	char	*dest;
	char	*tmp;

	i = -1;
	while (file[++i])
	{
		if (file[i] == '<')
		{
			start = i + 1;
			break ;
		}
	}
	while (file[i] != '>' && file[i] != '\0')
	{
		count++;
		i++;
	}
	tmp = ft_substr(file, 0, start - 1);
	dest = ft_substr(file, start, count - 1);
	ft_delete(&st->newfd);
	st->newfd = ft_strtrim(tmp, " ");
	ft_delete(&tmp);
	return (dest);
}

char		*ft_deleteleftfile(char *file)
{
	int		i;
	int		start;
	char	*str;

	i = -1;
	start = 0;
	while (file[++i])
	{
		if (file[i] == '>')
		{
			start = i;
			break ;
		}
	}
	while (file[i])
		i++;
	if (!(str = malloc(sizeof(char) * (i - start) + 1)))
		return (NULL);
	i = 0;
	while (file[start])
		str[i++] = file[start++];
	str[i] = '\0';
	ft_delete(&file);
	return (str);
}

void		ft_createnewfd(char *file, t_struct *st)
{
	int		i;
	char	**tmp;
	char	*tmp1;
	char	*str;

	i = 0;
	tmp = ft_strtokk(file, "<");
	str = ft_strdup("");
	while (tmp[i])
	{
		if (ft_strchr(tmp[i], '>') != NULL && i != 0)
			tmp[i] = ft_deleteleftfile(tmp[i]);
		str = ft_strfjoin(str, tmp[i], 1);
		i++;
	}
	ft_freetab(tmp);
	tmp1 = ft_strtrim(str, " ");
	if (!ft_strchr(str, '<'))
	{
		ft_delete(&st->newfd);
		st->newfd = ft_strdup(tmp1);
	}
	ft_delete(&str);
	ft_delete(&tmp1);
}

int			ft_checkmultipleleftred(char *file, t_struct *st)
{
	char	**tmp;
	char	*tmp1;
	int		i;

	tmp1 = ft_subleftfile(file, st, 0, 0);
	tmp = ft_strtokk(tmp1, "< ");
	ft_delete(&tmp1);
	i = 0;
	while (tmp[i])
	{
		if (ft_strcmp(st->newfd, tmp[i]) != 0)
		{
			if (ft_checkpath(tmp[i], st) == 0)
			{
				ft_freetab(tmp);
				return (0);
			}
		}
		i++;
	}
	ft_freetab(tmp);
	ft_createnewfd(file, st);
	return (1);
}

void		ft_searchpathforredir(char *path, t_struct *st)
{
	struct stat buffer;
	int			exist;

	exist = stat(path, &buffer);
	if (exist == 0)
	{
		ft_printf("minishell: %s : Is a directory\n", path);
		ft_delete(&st->newfd);
		st->newfd = ft_strdup("");
	}
}
