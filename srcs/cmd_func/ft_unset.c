/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:05:25 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/04 14:45:56 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_unsetloop(char **built_in, t_struct *st)
{
	st->i = 1;
	ft_redirectbuiltin(st);
	while (built_in[st->i] != NULL)
	{
		ft_unsetenv(built_in[st->i], st);
		st->i++;
	}
	ft_comebacktostdout(st);
}

int			ft_checkifok(char *str, char *var)
{
	int		i;

	i = 0;
	while (var[i])
	{
		if (var[i + 1] == '\0')
		{
			if (str[i + 1] == '=' || str[i + 1] == '\0')
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

char			**ft_copytabunset(char **src)
{
	char	**dest;
	int		len;
	int		i;

	len = ft_countenv(src);
	i = 0;
	if (!(dest = ft_calloc(sizeof(char*), (len + 1))))
		ft_printf("failed allocate memory to envp\n");
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

char		**ft_unsetenv(char *var, t_struct *st)
{
	int		index;

	index = ft_checkifenvexist(var, st->copyenvp);
	if (ft_checkvarisok(var) == 0)
	{
		ft_printf("minishell: unset: « %s » : not a valid identifier\n", var);
		st->exitstatus = EXIT_FAILURE;
		return (NULL);
	}
	else if (ft_checkifenvexist(var, st->copyenvp) != -1)
	{
		ft_freetab(st->copyenvp);
		st->copyenvp = ft_copytabunset(ft_deleteenv(index, st->copyenvp));
	}
	st->exitstatus = EXIT_SUCCESS;
	return (st->copyenvp);
}
