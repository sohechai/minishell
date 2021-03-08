/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlesignal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:00:43 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/08 17:24:36 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_handlesignal(int signum)
{
	int			status;

	if (signum == SIGINT)
	{
		signum = wait(&status);
		ft_printf("\n");
		if (signum == -1)
			ft_printf("\033[0;34mMinishell$> \033[0m", 1);
		g_exitstatus = 130;
	}
	else if (signum == SIGQUIT)
	{
		signum = wait(&status);
		if (signum != -1)
		{
			g_exitstatus = 131;
			ft_printf("^\\Quit: 3\n");
		}
	}
}
