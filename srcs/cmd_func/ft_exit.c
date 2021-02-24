/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:03:42 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/24 17:26:25 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				ft_lenuntilspace(int i, char *str)
{
	int count;

	count = 0;
	while(str[i] != '\0')
	{
		i++;
		count++;
		if (str[i] == ' ')
			return (count);
	}
	return (count);
}

int				ft_exit(char *cmd, t_struct *st)
{
	int		i;
	int		fd;

	i = 0;
	ft_printf("exit\n");
	if (st->redirection == DOUBLERED || st->redirection == SIMPLERED)
		fd = open(st->newfd, O_CREAT | O_RDWR | O_APPEND, 0640);
	while (cmd[i])
	{
		if (cmd[i] == ' ')
		{
			while (cmd[i] == ' ')
				i++;
			if (ft_isalpha(cmd[i]) != 0)
			{
				ft_printf("exit: %s : argument numérique nécessaire\n",
						ft_substr(cmd, i, ft_lenuntilspace(i, cmd)));
				break ;
			}
		}
		i++;
	}
	//ft_freetab(st->copyenvp);
	//ft_freestruct(st);
	// TODO faire fonction ft_exit qui free proprement tout ce qui a ete alloué
	exit(st->exitstatus);
	return (EXIT_SUCCESS);
}