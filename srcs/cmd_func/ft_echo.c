/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:10:09 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/01 13:59:19 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char				**rechange_character(char **cmd, size_t i, size_t n)
{
	while (cmd[n])
	{
		i = 0;
		while (cmd[n][i])
		{
			if (cmd[n][i] == -1)
				cmd[n][i] = '\\';
			if (cmd[n][i] == -2)
				cmd[n][i] = ';';
			if (cmd[n][i] == -3)
				cmd[n][i] = '|';
			if (cmd[n][i] == -4)
				cmd[n][i] = '>';
			if (cmd[n][i] == -5)
				cmd[n][i] = '<';
			if (cmd[n][i] == -8)
				cmd[n][i] = ' ';
			if (cmd[n][i] == -9)
				cmd[n][i] = '$';
			i++;
		}
		n++;
	}
	return (cmd);
}

int					ft_echo(t_struct *st, char **cmd)
{
	size_t		n;

	n = 1;
	ft_redirectbuiltin(st);
	if (cmd[1] != NULL)
	{
		while (cmd[n] && is_option(st, cmd[n], 1))
			n++;
		while (cmd[n])
		{
			ft_printf("%s", cmd[n]);
			n++;
			if (cmd[n])
				write(1, " ", 1);
		}
	}
	if (!st->op)
		ft_putchar('\n');
	ft_comebacktostdout(st);
	st->nquote = 0;
	st->op = 0;
	st->exitstatus = 0;
	return (1);
}
