/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initstruct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:45:23 by sohechai          #+#    #+#             */
/*   Updated: 2021/02/12 11:45:35 by sohechai         ###   ########lyon.fr   */
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
	st->i = 0;
	st->oldpwd = NULL;
	st->printerror = NULL;
	st->exitstatus = 0;
	return (st);
}
