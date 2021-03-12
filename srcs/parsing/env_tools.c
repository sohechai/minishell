/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 13:44:47 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/12 16:18:54 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		stock_env(t_struct *st, size_t j, char *str)
{
	st->env = ft_strndup(str, j);
	st->envi = ft_getenv(st->copyenvp, st->env);
}

void		delete_env(t_struct *st)
{
	ft_delete(&st->envi);
	ft_delete(&st->env);
}
