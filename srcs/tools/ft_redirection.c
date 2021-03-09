/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 21:07:44 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/09 17:20:18 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_checkfile(char *cmd, t_struct *st)
{
	char		**pathfile;
	struct stat buffer;
	int			exist;
	int			i;

	cmd = ft_strtrim(cmd, "< ");
	pathfile = ft_strtokk(cmd, "< ");
	i = 0;
	while (pathfile[i])
	{
		exist = stat(pathfile[i], &buffer);
		if (ft_strchr(pathfile[i], '>'))
		{
			i++;
			st->redirection = SIMPLERED;
			if (ft_strchr(pathfile[i], '>'))
			{
				st->redirection = DOUBLERED;
				i++;
			}
		}
		else if (exist == 0)
			st->stop = 0;
		else
		{
			ft_printf("minishell: %s: No such file or directory\n",
				pathfile[i]);
			ft_freetab(pathfile);
			free(cmd);
			st->stop = 1;
			return (0);
		}
		i++;
	}
	free(cmd);
	ft_freetab(pathfile);
	return (0);
}

int			ft_checkpath(char *cmd, t_struct *st)
{
	char		*pathfile;
	struct stat buffer;
	int			len;
	int			exist;

	len = ft_strlen(cmd) - ft_lenoffile(cmd);
	pathfile = ft_substr(cmd, 0, len);
	if (!ft_strncmp(pathfile, "~", 1))
	{
		st->envi = ft_getenv(st->copyenvp, "HOME");
		st->tempo = ft_strtrim(pathfile, "~");
		free(pathfile);
		pathfile = ft_strjoin(st->envi, st->tempo);
		ft_delete(&st->tempo);
	}
	exist = lstat(pathfile, &buffer);
	if (exist == 0)
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
	return (0);
}

int			ft_openmultiplefiles(int i, t_struct *st)
{
	int			fd;

	while (st->files[i] != NULL)
	{
		if (st->files[i + 1] != NULL)
		{
			if (ft_lenoffile(st->files[i]) != -1)
			{
				if (ft_checkpath(st->files[i], st) == 0)
					return (0);
			}
			fd = open(st->files[i], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR |
				S_IRGRP | S_IWGRP | S_IWUSR);
			close(fd);
		}
		if (st->stop == 1)
		{
			fd = open(st->files[i], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR |
				S_IRGRP | S_IWGRP | S_IWUSR);
			close(fd);
		}
		i++;
	}
	return (i);
}

int			ft_redirection(char *cmd, t_struct *st)
{
	int			i;
	char		*tmp;

	i = 0;
	if (ft_indexuntilfile(cmd, st) == 0)
		return (0);
	if (st->redirection != 0)
	{
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
		{
			free(st->newfd);
			st->newfd = ft_strdup(tmp);
			if (ft_strchr(st->newfd, '<'))
				ft_checkmultipleleftred(st->newfd, st);
			else if (ft_lenoffile(st->newfd) != -1)
				ft_searchpathforredir(st->newfd, st);
			st->files = ft_strtokk(st->newfd, " >|");
			i = ft_openmultiplefiles(i, st);
			if (i > 1)
			{
				free(st->newfd);
				st->newfd = ft_strdup(st->files[i - 1]);
				if (ft_lenoffile(st->newfd) != -1)
				{
					if (ft_checkpath(st->newfd, st) == 0)
						return (0);
				}
				ft_freetab(st->files);
			}
			else
			{
				ft_delete(&st->newfd);
				st->newfd = ft_strdup(st->files[0]);
				ft_freetab(st->files);
			}
		}
		ft_delete(&tmp);
	}
	return (EXIT_SUCCESS);
}
