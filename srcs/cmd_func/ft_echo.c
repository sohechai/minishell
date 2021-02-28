/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:10:09 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/28 16:14:16 by sohechai         ###   ########lyon.fr   */
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
			if (cmd[n][i] == -6)
				cmd[n][i] = '\"';
			if (cmd[n][i] == -7)
				cmd[n][i] = '\'';
			if (cmd[n][i] == -8)
				cmd[n][i] = ' ';
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
	if (cmd[1] != NULL)
	{
		while (is_option(st, cmd[n], 1))
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
	st->nquote = 0;
	st->op = 0;
	return (1);
}
