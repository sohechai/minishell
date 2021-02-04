/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 16:48:38 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/04 18:30:06 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_countenv(char **env)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while(env[i] != NULL)
	{
		i++;
	}
	return (i);
}

// TODO malloc ? free ? v

char **ft_sortenv(char **envp)
{
	int size;
	int		i;
	char	*tmp;
	char	**sortenv;

	size = ft_countenv(envp);
	i = 0;
	sortenv = envp;
	while (i < size - 1)
	{
		if ((ft_strcmp(envp[i], envp[i + 1])) > 0)
		{
			tmp = envp[i];
			sortenv[i] = envp[i + 1];
			sortenv[i + 1] = tmp;
			i = 0;
		}
		else
			++i;
	}
	return (sortenv);
}

void		ft_printsortenv(t_struct *st)
{
	char	**printsortenv;
	int		i;

	printsortenv = ft_sortenv(st->copyenvp);
	i = 0;
	while (printsortenv[i])
		ft_printf("declare -x %s\n", printsortenv[i++]);
}
