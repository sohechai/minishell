/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkvar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:16:09 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/24 14:48:59 by sohechai         ###   ########lyon.fr   */
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
	if (st->copyenvp == NULL)
		ft_printf("No environment :\n");
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

int		ft_isalphaandequal(int c)
{
	if ((65 <= c && c <= 90) || (97 <= c && c <= 122) || c == '=')
		return (c);
	else
		return (0);
}

int				ft_checkvarisok(char *var)
{
	int		i;

	i = 0;
	while (var[i])
	{
		if (ft_isalphaandequal(var[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
