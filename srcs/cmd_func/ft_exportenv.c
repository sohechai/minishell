/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exportenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:10:53 by sohechai          #+#    #+#             */
/*   Updated: 2021/02/05 16:12:03 by sohechai         ###   ########lyon.fr   */
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
	return (i);
}

int			ft_exportenv(char *var, t_struct *st)
{
	int		index;

	index = ft_checkvarismissing(var, st);
	st->copyenvp[index] = ft_strdup(var);
	return (0);
}
