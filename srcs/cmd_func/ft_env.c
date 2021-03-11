/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:41:08 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/11 14:33:21 by sofiahechai      ###   ########lyon.fr   */
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
