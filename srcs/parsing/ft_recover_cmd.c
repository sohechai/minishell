/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recover_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:15:57 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/04 15:16:00 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_recover_cmd(t_mini *mi)
{
	size_t		i;
	size_t		n;

	n = 0;
	if (!(mi->cmd = (char**)malloc(sizeof(char*) * mi->semi + 1)))
		return (0);
	while (n < mi->semi)
	{
		i = 0;
		if (mi->tab_arg[n][0] == '\0')
			break ;
		while (mi->tab_arg[n][i] && mi->tab_arg[n][i] != ' ')
			i++;
		mi->cmd[n] = ft_strndup(mi->tab_arg[n], i);
		n++;
		if (n >= mi->semi)
			break ;
	}
	return (1);
}
