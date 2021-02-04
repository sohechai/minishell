/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:14:05 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/04 15:14:22 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				count(t_mini *mi, int count, int i)
{
	while (mi->line[i] == '|' || mi->line[i] == ' '
			|| mi->line[i] == '\t')
	{
		if (mi->line[i] == '|')
			count++;
		if (count == 3)
			return (ft_error('|', count));
		i++;
	}
	return (1);
}

/*
 *	Verifie si les pipes entrées sont possibles.
 */

int				check_pipe(t_mini *mi)
{
	int		i;

	i = 0;
	while (mi->line[i])
	{
		if (mi->line[i] == '|' && mi->line[i + 1] == '|'
			&& mi->line[i + 2] == '|')
		{
			if (mi->line[i + 3] == '|')
				i = 2;
			return (ft_error('|', i));
		}
		if (mi->line[i] == '|' && mi->line[i + 1] != '\0')
		{
			if (count(mi, 1, i) == 0)
				return (0);
		}
		i++;
	}
	return (1);
}
