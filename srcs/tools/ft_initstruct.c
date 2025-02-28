/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initstruct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:45:23 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/13 17:14:34 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			ft_initstructnext(t_struct *st)
{
	st->i = 0;
	st->index = 0;
	st->pipecmd = 0;
	g_exitstatus = 0;
	st->redirection = 0;
	st->oldstdout = 0;
	st->stop = 0;
	st->fdinput = 0;
	st->pid = 0;
	st->line = NULL;
	st->tab_arg = NULL;
	st->error = 0;
	st->tab_pipe = 0;
	st->quote = 0;
	st->nquote = 0;
	st->islast = 0;
	st->op = 0;
	st->semi = 0;
	st->fd = 1;
	st->nbackslash = 0;
	st->nredir = 0;
}

t_struct		*ft_initstruct(void)
{
	t_struct *st;

	if (!(st = malloc(sizeof(t_struct) * 1)))
		return (NULL);
	st->line = NULL;
	st->tab_arg = NULL;
	st->error = 0;
	st->tab_pipe = 0;
	st->quote = 0;
	st->nquote = 0;
	st->islast = 0;
	st->op = 0;
	st->semi = 0;
	st->fd = 1;
	st->copyenvp = NULL;
	st->parsecmd = NULL;
	st->oldpwd = NULL;
	st->newfd = NULL;
	st->printerror = NULL;
	st->pathfile = NULL;
	ft_initstructnext(st);
	return (st);
}
