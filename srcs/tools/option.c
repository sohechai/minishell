/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:03:13 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/23 15:56:34 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		check_op(t_mini *mi, char *str, size_t i)
{
	while (str[i] == 'n')
	{
		i++;
	}
	if (str[i] != '\0')
		return (0);
	mi->op = 1;
	return (1);
}

int				is_option(t_mini *mi, char *str, size_t i)
{
	if (str[0] == '-' && check_op(mi, str, i))
		return (1);
	return (0);
}
