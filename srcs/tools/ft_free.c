/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:44:41 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/04 14:20:47 by sofiahechai      ###   ########lyon.fr   */
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
	// if (st->env)
	// 	free(st->env);
	// if (st->newfd)
	// 	free(st->newfd);
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
