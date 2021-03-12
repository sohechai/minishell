/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:41:08 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/12 12:47:37 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_env(char **envp, t_struct *st)
{
	int i;

	i = 0;
	ft_redirectbuiltin(st);
	while (envp[i] != NULL)
	{
		if (ft_strchr(envp[i], '=') != NULL)
			ft_printf("%s\n", envp[i]);
		i++;
	}
	ft_comebacktostdout(st);
}
