/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkvar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:16:09 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/09 12:57:52 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				ft_strlenuntil_equal(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

int				checkvarloop(t_struct *st, char *var, char *lessvar, int i)
{
	int		len;

	len = ft_strlenuntil_equal(st->copyenvp[i]);
	if ((ft_strncmp(ft_strnstr(st->copyenvp[i], lessvar, len),
					lessvar, len) != 0))
		i++;
	else if (!ft_strchr(var, '='))
	{
		ft_delete(&lessvar);
		return (-2);
	}
	ft_delete(&lessvar);
	return (i);
}

int				ft_checkvarismissing(char *var, t_struct *st)
{
	int		i;
	int		len;
	char	*lessvar;

	lessvar = ft_getvar(var);
	i = 0;
	len = ft_strlen(lessvar);
	if (st->copyenvp == NULL)
		ft_printf("minishell: No environment :\n");
	while (st->copyenvp[i] != NULL)
	{
		if (ft_strnstr(st->copyenvp[i], lessvar, len))
			return (checkvarloop(st, var, lessvar, i));
		i++;
	}
	free(lessvar);
	return (-1);
}

int				ft_isalphaandequal(int c, int tmp, int i)
{
	if (ft_isalpha(c) || c == '=' || c == '/' || c == '_')
		return (c);
	else if (ft_isdigit(c) && tmp < i)
		return (c);
	else
		return (0);
}

int				ft_checkvarisok(char *var)
{
	int		i;
	int		tmp;

	i = 0;
	tmp = 0;
	while (var[i])
	{
		if (!ft_isalphaandequal(var[i], tmp, i) || var[0] == '=')
			return (0);
		if (var[i] == '=')
			tmp = i;
		i++;
	}
	return (1);
}
