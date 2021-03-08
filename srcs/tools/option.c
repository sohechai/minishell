/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:03:13 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/08 17:06:15 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		check_op(t_struct *st, char *str, size_t i)
{
	while (str[i] == 'n')
		i++;
	if (i == 1 || str[i] != '\0')
		return (0);
	st->op = 1;
	return (1);
}

int				is_option(t_struct *st, char *str, size_t i)
{
	if (str[0] == '-' && check_op(st, str, i))
		return (1);
	return (0);
}
