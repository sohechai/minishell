/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_semi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:15:00 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/04 15:15:14 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				check_semi(t_mini *mi)
{
	size_t		i;

	i = 0;
	while (mi->line[i])
	{
		if (mi->line[i] == ';' && mi->line[i + 1] == ';')
		{
			ft_error(';', 1);
			return (0);
		}
		i++;
	}
	return (1);
}
