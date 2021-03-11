/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getabsolutepath.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 14:12:13 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/10 13:54:04 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_exist(t_struct *st, char *pathfile, int exist)
{
	if (!exist)
	{
		st->stop = 0;
		ft_delete(&pathfile);
		return (1);
	}
	else
	{
		ft_printf("minishell: %s: No such file or directory\n", pathfile);
		ft_delete(&pathfile);
		st->stop = 1;
		return (0);
	}
}

char		*dup_and_free(char *del, char *src)
{
	char	*ret;

	ft_delete(&del);
	ret = ft_strdup(src);
	return (ret);
}

static int	which_redir(t_struct *st, char *tmp, int i)
{
	if (ft_strchr(tmp, '<'))
		ft_checkmultipleleftred(tmp, st);
	else if (ft_lenoffile(tmp) != -1)
		ft_searchpathforredir(tmp, st);
	if (!st->newfd)
		st->newfd = dup_and_free(st->newfd, tmp);
	st->files = ft_strtokk(st->newfd, " >|");
	i = ft_openmultiplefiles(i, st);
	if (i > 1)
	{
		st->newfd = dup_and_free(st->newfd, st->files[i - 1]);
		if (ft_lenoffile(st->newfd) != -1)
			if (ft_checkpath(st->newfd, st) == 0)
				return (0);
		ft_freetab(st->files);
	}
	else
	{
		st->newfd = dup_and_free(st->newfd, st->files[0]);
		ft_freetab(st->files);
	}
	return (1);
}

int			is_redirection(char *cmd, char *tmp, t_struct *st)
{
	int		i;

	i = 0;
	tmp = ft_strdup(cmd + ft_indexuntilfile(cmd, st));
	st->newfd = ft_strtrim(tmp, " ");
	free(tmp);
	tmp = ft_strdup(st->newfd);
	if (st->redirection == LEFTRED)
		st->leftredir = 1;
	else
		st->leftredir = 0;
	if (st->leftredir == 1)
		ft_checkfile(tmp, st);
	if (st->redirection == SIMPLERED || st->redirection == DOUBLERED)
		if (!which_redir(st, tmp, i))
			return (0);
	ft_delete(&tmp);
	return (1);
}
