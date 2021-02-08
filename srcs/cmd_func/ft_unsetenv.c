/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:05:25 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/08 17:16:16 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_checkifok(char *str, char *var)
{
	int		i;

	i = 0;
	while (var[i])
	{
		if (var[i + 1] == '\0')
		{
			if(str[i + 1] == '=' || str[i + 1] == '\0')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int			ft_checkifenvexist(char *var, char **envp)
{
	int		len;
	int		i;

	len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], var, len) != NULL)
		{
			if (ft_checkifok(envp[i], var) == 1)
				return (i);
			else
				return (-1);
		}
		i++;
	}
	return (-1);
}

char		**ft_deleteenv(int index, char **envp)
{
	int		i;
	int		j;
	char	**newenvp;

	i = 0;
	j = 0;
	newenvp = envp;
	while (envp[i])
	{
		if (i == index)
		{
			i++;
		}
		newenvp[j++] = envp[i++];
	}
	newenvp[j] = NULL;
	return (newenvp);
}

char		**ft_unsetenv(char *var, t_struct *st)
{
	int		index;

	index = ft_checkifenvexist(var, st->copyenvp);
	if(ft_strchr(var, '='))
		ft_printf("unset: « %s » : identifiant non valable\n", var);
	else if (ft_checkifenvexist(var, st->copyenvp) != -1)
	{
		st->copyenvp = ft_deleteenv(index, st->copyenvp);
	}
	return (st->copyenvp);
}

// int		main(int ac, char **av, char **envp)
// {
// 	int		i = 0;
// 	if (ac < 1)
// 		printf("dkj");
// 	(void)av;
// 	char **newone = ft_unsetenv("dksfj", envp);
// 	while (newone[i])
// 	{
// 		printf("%s\n", newone[i++]);
// 	}
// 	return(0);
// }