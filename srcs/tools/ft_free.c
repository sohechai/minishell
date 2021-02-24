/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:44:41 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/24 17:24:54 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_freestruct(t_struct *st)
{
	// if (st->copyenvp)
	// 	ft_freetab(st->copyenvp);
	// if(st->oldpwd)
	// 	free(st->oldpwd);
	// if(st->printerror)
	// 	free(st->printerror);
	// if (st->newfd)
	// 	free(st->newfd);
	free(st);
}

void		ft_freetab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
}
