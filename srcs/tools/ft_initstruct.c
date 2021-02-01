/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initstruct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:45:23 by sohechai          #+#    #+#             */
/*   Updated: 2021/02/01 15:54:32 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env		*ft_initstruct(void)
{
	t_env *st;

	if (!(st = malloc(sizeof(t_env) * 1)))
		return (NULL);
	st->env = NULL;
	return (st);
}
