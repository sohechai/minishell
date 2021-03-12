/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:44:41 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/11 13:38:37 by sofiahechai      ###   ########lyon.fr   */
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
		ft_delete(&st->oldpwd);
	st->leftredir = 0;
	st->stop = 0;
	if (st->newfd)
		ft_delete(&st->newfd);
}

void		ft_freetab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != NULL)
		ft_delete(&tab[i++]);
	free(tab);
}
