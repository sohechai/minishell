/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:41:08 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/12 11:41:17 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_env(char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strchr(envp[i], '=') != NULL)
			ft_printf("%s\n", envp[i]);
		i++;
	}
}
