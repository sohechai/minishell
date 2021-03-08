/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:51:31 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/08 17:21:35 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				check_pipe(t_struct *st)
{
	int		i;

	i = 0;
	while (st->line[i])
	{
		if (st->line[i] == '"' || st->line[i] == '\'')
			i = advance(st->line, i + 1, st->line[i]);
		if (st->line[i] == '|' && st->line[i + 1] == '|'
			&& st->line[i + 2] == '|')
		{
			if (st->line[i + 3] == '|')
				i = 2;
			return (ft_error('|', i));
		}
		if (st->line[i] == '|' && endline(st->line, i + 1))
			return (ft_error('|', 1));
		i++;
	}
	return (1);
}
