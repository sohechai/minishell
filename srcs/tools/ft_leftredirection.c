/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_leftredirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:16:12 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/10 14:25:25 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char		*ft_subleftfile(char *file, t_struct *st)
{
	int		i;
	int		count;
	int		start;
	char	*dest;

	i = 0;
	count = 0;
	start = 0;
	while (file[i])
	{
		if (file[i] == '<')
		{
			start = i + 1;
			break ;
		}
		i++;
	}
	while (file[i] != '>' && file[i] != '\0')
	{
		count++;
		i++;
	}
	st->newfd = ft_strtrim((ft_substr(file, 0, start - 1)), " ");
	dest = ft_substr(file, start, count - 1);
	return (dest);
}

void		ft_createnewfd(char *file, t_struct *st)
{
	int		i;
	char	**tmp;
	char	*str;

	i = 0;
	tmp = ft_strtokk(file, " ");
	str = ft_strdup("");
	while (tmp[i])
	{
		if (!ft_strcmp(tmp[i], "<") && tmp[i + 2] != NULL)
			i += 2;
		else
		{
			str = ft_strfjoin(str, tmp[i], 1);
			i++;
		}
	}
	ft_freetab(tmp);
	str = ft_strtrim(str, " ");
	if (!ft_strchr(str, '<'))
	{
		ft_delete(&st->newfd);
		st->newfd = ft_strdup(str);
	}
	ft_delete(&str);
}

int			ft_checkmultipleleftred(char *file, t_struct *st)
{
	char	**tmp;
	char	*tmp1;
	int		i;

	tmp1 = ft_subleftfile(file, st);
	tmp = ft_strtokk(tmp1, "< ");
	ft_delete(&tmp1);
	i = 0;
	while (tmp[i])
	{
		if (ft_strcmp(st->newfd, tmp[i]) != 0)
		{
			if (ft_checkpath(tmp[i], st) == 0)
				return (0);
		}
		i++;
	}
	ft_freetab(tmp);
	ft_createnewfd(file, st);
	return (1);
}

void			ft_searchpathforredir(char *path, t_struct *st)
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
