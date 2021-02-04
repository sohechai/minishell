/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:16:51 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/04 15:16:55 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini		*ft_init_mini(t_mini *mi)
{
	if (!(mi = malloc(sizeof(t_mini))))
		return (0);
	mi->echo = NULL;
	mi->line = NULL;
	mi->tab_arg = NULL;
	mi->tab_pipe = NULL;
	mi->cmd = NULL;
	mi->semi = 0;
	mi->islast = 0;
	mi->op = 0;
	mi->nquote = 0;
	return (mi);
}

void 		ft_reset_mi(t_mini *mi)
{
	mi->echo = NULL;
	mi->line = NULL;
	mi->tab_arg = NULL;
	mi->cmd = NULL;
	mi->semi = 0;
	mi->islast = 0;
	mi->op = 0;
	mi->nquote = 0;
	ft_delete(&mi->line);
}

void		ft_free_mi(t_mini *mi)
{
	ft_delete(&mi->line);
	ft_free_tab(mi->tab_arg);
	ft_free_tab(mi->cmd);
}
