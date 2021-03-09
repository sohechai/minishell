/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_leftredirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:16:12 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/09 17:21:06 by sohechai         ###   ########lyon.fr   */
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
	st->newfd = ft_substr(file, 0, start - 1);
	dest = ft_substr(file, start, count - 1);
	return (dest);
}

void		ft_createnewfd(char *file, t_struct *st)
{
	int		i;
	char **tmp;
	char	*str;

	i = 0;
	tmp = ft_strtokk(file, " ");
	// ft_delete(&st->newfd);
	str = ft_strdup("");
	while (tmp[i])
	{
		if (!ft_strcmp(tmp[i], "<") && tmp[i + 2] != NULL)
			i += 2;
		else
		{
			str = ft_strjoin(str, tmp[i]);
			i++;
		}
	}
	st->newfd = ft_strdup(str);
}

int			ft_checkmultipleleftred(char *file, t_struct *st)
{
	char	**tmp;
	int		i;

	tmp = ft_strtokk(ft_subleftfile(file, st), "< \0");
	i = 0;
	while (tmp[i])
	{
		if (ft_checkpath(tmp[i], st) == 0)
			return (0);
		i++;
	}
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
		st->newfd = ft_strdup("");
	}
}
