/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:51:31 by sohechai          #+#    #+#             */
/*   Updated: 2021/02/28 16:14:16 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				count(t_struct *st, int count, int i)
{
	while (st->line[i] == '|' || st->line[i] == ' '
			|| st->line[i] == '\t')
	{
		if (st->line[i] == '|')
			count++;
		if (count == 3)
			return (ft_error('|', count));
		i++;
	}
	return (1);
}

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
			return (ft_error('|', i));
		}
		if (st->line[i] == '|' && st->line[i + 1] != '\0')
		{
			if (count(st, 1, i) == 0)
				return (0);
		}
		i++;
	}
	return (1);
}
