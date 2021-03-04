/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlesignal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:00:43 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/04 23:50:29 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_struct st;

void		ft_handlesignal(int signum)
{
	int			status;

	if (signum == SIGINT)
	{
		signum = wait(&status);
		ft_printf("\n");
		if (signum == -1)
			ft_printf("\033[0;34mMinishell$> \033[0m", 1);
		// st->exitstatus = 130;
	}
	else if (signum == SIGQUIT)
	{
		signum = wait(&status);
		if (signum != -1)
			ft_printf("^\\Quit: 3\n");
	}
}