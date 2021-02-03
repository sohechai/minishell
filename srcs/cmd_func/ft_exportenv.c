/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exportenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:47:24 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/03 21:13:21 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_deleteenv(t_struct *st)
{
	size_t	i;

	i = 0;
	while ((st->copyenvp)[i] != NULL)
		ft_freetab(st->copyenvp[i++]);
	(st->copyenvp)[i] = NULL;
}

void	ft_freetab(char **tab)
{
	if (tab != NULL)
	{
		free(*tab);
		*tab = NULL;
	}
}

static int		ft_getindex(t_struct *st, const char *name)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (st->copyenvp == NULL)
		ft_printf("No environment :\n");
	while (st->copyenvp[i] != NULL)
	{
		while (st->copyenvp[i][j] && name[j] && st->copyenvp[i][j] == name[j])
		{
			if (st->copyenvp[i][j + 1] == '=')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

static char		**ft_addenv(t_struct *st, char *value)
{
	char	**copy;
	size_t	i;

	i = 0;
	while (st->copyenvp[i] != NULL)
		i++;
	copy = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (st->copyenvp[++i] != NULL)
		copy[i] = ft_strdup(st->copyenvp[i]);
	copy[i++] = ft_strdup(value);
	copy[i] = NULL;
	ft_deleteenv(&st->copyenvp);
	return (copy);
}

int				ft_exportenv(t_struct *st, const char *name, const char *value, int overwrite)
{
	int		iex;
	char	*temp;
	char	*hold;
	// int		i;

	// i = 0;
	if (!*name || !*value)
		return (0);
	iex = ft_getindex(st->copyenvp, name);
	temp = ft_strdup(name);
	hold = temp;
	temp = ft_strjoin(hold, "=");
	if (hold != NULL)
		ft_freetab(&hold);
	else
		return (0);
	hold = temp;
	temp = ft_strjoin(temp, value);
	if (hold != NULL)
		ft_freetab(&hold);
	else
		return (0);
	if (iex == -1 && overwrite == 0)
		st->copyenvp = ft_addenv(st->copyenvp, temp);
	else
		(st->copyenvp)[iex] = ft_strdup(temp);
	ft_freetab(&temp);
	return (1);
}