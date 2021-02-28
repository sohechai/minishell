/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlesignal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:00:43 by sohechai          #+#    #+#             */
/*   Updated: 2021/02/28 15:02:12 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_sigint(int signum)
{
	pid_t pid;

	pid = signum;
	if (kill(pid, signum) < 0)
	{
		ft_printf("\n");
		ft_printf("\033[0;34mMinishell$> \033[0m");
	}
}

void		ft_sigquit(int signum)
{
	pid_t pid;

	pid = signum;
	if (kill(pid, signum) == 3)
		ft_printf("Quit: 3\n");
}
