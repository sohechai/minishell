/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 21:07:44 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/12 00:12:58 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_file_loop(t_struct *st, char **pathfile, int i)
{
	int			exist;
	struct stat buffer;

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
		st->stop = 1;
		return (0);
	}
	return (1);
}

int			ft_checkfile(char *cmd, t_struct *st)
{
	char		**pathfile;
	int			i;

	cmd = ft_strtrim(cmd, "< ");
	pathfile = ft_strtokk(cmd, "< ");
	i = 0;
	while (pathfile[i])
	{
		if (!check_file_loop(st, pathfile, i))
		{
			ft_delete(&cmd);
			ft_freetab(pathfile);
			return (0);
		}
		if (pathfile[i + 1] == NULL)
			st->newfd = dup_and_free(st->newfd, pathfile[i]);
		i++;
	}
	ft_delete(&cmd);
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
		ft_delete(&pathfile);
		pathfile = ft_strjoin(st->envi, st->tempo);
		ft_delete(&st->tempo);
	}
	exist = lstat(pathfile, &buffer);
	return (ft_exist(st, pathfile, exist));
}

int			ft_openmultiplefiles(int i, t_struct *st)
{
	int			fd;

	while (st->files[i] != NULL)
	{
		if (st->files[i + 1] != NULL)
		{
			if (ft_lenoffile(st->files[i]) != -1)
				if (ft_checkpath(st->files[i], st) == 0)
					return (0);
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
	char		*tmp;

	tmp = NULL;
	if (ft_indexuntilfile(cmd, st) == 0)
		return (0);
	if (st->redirection != 0)
		is_redirection(cmd, tmp, st);
	return (EXIT_SUCCESS);
}
