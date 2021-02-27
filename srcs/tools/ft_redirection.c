/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 21:07:44 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/27 16:30:12 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_redirectbuiltin(t_struct *st)
{
	int		fd;

	st->oldstdout = dup(1);
	if (st->redirection == SIMPLERED || st->redirection == DOUBLERED)
	{
		if (st->redirection == DOUBLERED)
			fd = open(st->newfd, O_CREAT | O_RDWR | O_APPEND, 0640);
		else
			fd = open(st->newfd, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR |
				S_IRGRP | S_IWGRP | S_IWUSR);
		close(1);
		dup(fd);
		close(fd);
	}
}

void		ft_comebacktostdout(t_struct *st)
{
	if (st->redirection == SIMPLERED || st->redirection == DOUBLERED)
	{
		dup2(st->oldstdout, 1);
		close(st->oldstdout);
	}
}

int		ft_checkfile(char *cmd, t_struct *st)
{
	char		*pathfile;
	struct stat buffer;
	int			len;
	int			exist;

	len = ft_strlen(cmd) - (ft_indexuntilfile(cmd, st) + ft_lenoffile(cmd)) - 1;
	pathfile = ft_substr(cmd, ft_indexuntilfile(cmd, st), len);
	exist = stat(pathfile, &buffer);
	if (exist == 0)
	{
		st->stop = 0;
		return (1);
	}
	else
	{
		ft_printf("%s: No such file or directoryyy\n", pathfile);
		st->stop = 1;
		return (0);
	}
	return (0);
}
