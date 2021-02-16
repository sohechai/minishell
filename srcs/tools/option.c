/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:03:13 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/16 12:03:22 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			option(t_mini *mi, size_t i, size_t n)
{
	while (mi->tab_arg[n][i])
	{
		if (mi->tab_arg[n][i] == '-')
		{
			i++;
			while (mi->tab_arg[n][i] == 'n')
				i++;
			if (mi->tab_arg[n][i] == '\0')
			{
				mi->op = i;
				break ;
			}
			if (!ft_strchr(" \0", mi->tab_arg[n][i]))
				break ;
			mi->op = i;
		}
		i++;
	}
}
