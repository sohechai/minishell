/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exportenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:10:53 by sohechai          #+#    #+#             */
/*   Updated: 2021/02/08 13:49:48 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char			*ft_getvar(char *var)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	j = 0;
	len = ft_strlen(var);
	while (var[i])
	{
		if (var[i] == '=')
			break ;
		i++;
	}
	tmp = ft_substr(var, 0, i + 1);
	return (tmp);
}

int				ft_checkvarismissing(char *var, t_struct *st)
{
	int		i;
	int		len;
	char	*lessvar;

	lessvar = ft_getvar(var);
	i = 0;
	len = ft_strlen(lessvar);
	while (st->copyenvp[i] != NULL)
	{
		if (ft_strnstr(st->copyenvp[i], lessvar, len))
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

void			ft_exportenv(char *var, t_struct *st)
{
	int		i;
	int		index;
	int		len;

	i = 0;
	index = ft_checkvarismissing(var, st);
	len = ft_countenv(st->copyenvp);
	if (index != -1)
		st->copyenvp[index] = ft_strdup(var);
	else
	{
		while (st->copyenvp[i] != NULL)
			i++;
		st->copyenvp[i] = ft_strdup(var);
		st->copyenvp[i + 1] = NULL;
	}
}
