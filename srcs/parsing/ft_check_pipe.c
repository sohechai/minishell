/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:51:31 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/04 15:16:45 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				check_pipe(t_struct *st)
{
	int		i;

	i = 0;
	while (st->line[i])
	{
		if (st->line[i] == '|' && st->line[i + 1] == '|'
			&& st->line[i + 2] == '|')
		{
			if (st->line[i + 3] == '|')
				i = 2;
			return (ft_error('|', i, st));
		}
		if (st->line[i] == '|' && endline(st->line, i + 1))
			return (ft_error('|', 1, st));
		i++;
	}
	return (1);
}
