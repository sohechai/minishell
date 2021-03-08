/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:03:42 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/08 13:29:02 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				ft_lenuntilspace(int i, char *str)
{
	int count;

	count = 0;
	while (str[i] != '\0')
	{
		i++;
		count++;
		if (str[i] == ' ')
			return (count);
	}
	return (count);
}

int				ft_isnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int				ft_checkexitargs2(int i, char *cmd)
{
	if (ft_isalpha(cmd[i]) != 0)
	{
		ft_printf("minishell: exit: %s : numeric argument required\n",
				ft_substr(cmd, i, ft_lenuntilspace(i, cmd)));
		return (1);
	}
	return (0);
}

int				ft_checkexitargs(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i++])
	{
		if (cmd[i] == ' ')
		{
			while (cmd[i] == ' ')
				i++;
			ft_checkexitargs2(i, cmd);
			if (ft_isnum(cmd[i]) != 0)
			{
				while (ft_isnum(cmd[i]))
					i++;
				if (cmd[i])
				{
					ft_printf("minishell: exit: too many arguments\n");
					return (0);
				}
				else
					exit(ft_atoi(cmd));
			}
		}
	}
	return (1);
}

int				ft_exit(char *cmd, t_struct *st)
{
	int		fd;

	ft_printf("exit\n");
	if (st->redirection == DOUBLERED || st->redirection == SIMPLERED)
	{
		fd = open(st->newfd, O_CREAT | O_RDWR | O_APPEND, 0640);
		free(st->newfd);
		exit(exitstatus);
		close(fd);
	}
	// ft_freeloop(st);
	//ft_freetab(st->copyenvp);
	//ft_freestruct(st);
	// TODO faire fonction ft_exit qui free proprement tout ce qui a ete alloué
	if (ft_checkexitargs(cmd) == 1)
		printf("a\n");
		// exit(exitstatus);
	return (EXIT_SUCCESS);
}
