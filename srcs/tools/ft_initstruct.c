/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initstruct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:45:23 by sohechai          #+#    #+#             */
/*   Updated: 2021/02/08 15:19:16 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_mini			*ft_initmini(void)
{
	t_mini	*mi;

	if (!(mi = malloc(sizeof(t_mini) * 1)))
		return (NULL);
	mi->line = NULL;
	mi->tab_arg = NULL;
	mi->cmd = NULL;
	mi->echo = NULL;
	mi->error = 0;
	mi->tab_pipe = 0;
	mi->quote = 0;
	mi->nquote = 0;
	mi->islast = 0;
	mi->op = 0;
	mi->semi = 0;
	return (mi);
}

t_struct		*ft_initstruct(void)
{
	t_struct *st;

	if (!(st = malloc(sizeof(t_struct) * 1)))
		return (NULL);
	st->copyenvp = NULL;
	st->sortenv = NULL;
	st->i = 0;
	st->oldpwd = NULL;
	return (st);
}

