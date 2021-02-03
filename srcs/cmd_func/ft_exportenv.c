/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exportenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:47:24 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/03 17:29:29 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	char	**cpy;
	size_t	i;

	i = 0;
	while (st->copyenvp[i] != NULL)
		i++;
	cpy = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (st->copyenvp[++i] != NULL)
		cpy[i] = ft_strdup(st->copyenvp[i]);
	cpy[i++] = ft_strdup(value);
	cpy[i] = NULL;
	ft_make_env_del(&st->copyenvp);
	return (cpy);
}

int				ft_setenv(t_struct *st,\
const char *name, const char *value, int overwrite)
{
	int		index;
	char	*temp;
	char	*hold;
	// int		i;

	// i = 0;
	if (!*name || !*value)
		return (0);
	index = ft_get_index(st->copyenvp, name);
	temp = ft_strdup(name);
	hold = temp;
	temp = ft_strjoin(hold, "=");
	if (hold != NULL)
		ft_strdel(&hold)
	else
		return (0);
	hold = temp;
	temp = ft_strjoin(temp, value);
	(hold != NULL) ? ft_strdel(&hold) : NULL;
	if (index == -1 && overwrite == 0)
		*st->copyenvp = ft_add_env(*st->copyenvp, temp);
	else
		(*st->copyenvp)[index] = ft_strdup(temp);
	ft_strdel(&temp);
	return (1);
}