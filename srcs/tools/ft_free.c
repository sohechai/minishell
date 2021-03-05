/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:44:41 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/05 15:29:57 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_freestruct(t_struct *st)
{
	free(st);
}

void		ft_freeloop(t_struct *st)
{
	if (st->tab_arg)
		ft_freetab(st->tab_arg);
	if (st->tab_pipe)
		free(st->tab_pipe);
	if (st->oldpwd)
		free(st->oldpwd);
	// if (st->pwd)
	// 	free(st->pwd);
	// if (st->envi)
	// 	free(st->envi);
	if (st->newfd)
		ft_delete(&st->newfd);
	// if (st->files)
	// 	free(st->files);
}

void		ft_freetab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
}
