/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkvar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:16:09 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/12 11:42:30 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int				ft_checkvarisok(char *var)
{
	int		i;

	i = 0;
	if (ft_strchr(var, '='))
		return (1);
	while (var[i])
	{
		if (ft_isalpha(var[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
