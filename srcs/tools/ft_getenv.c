/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:59:54 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/12 12:49:51 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_strlenequal(char *str)
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

char		*ft_getenv(char **copyenvp, char *var)
{
	int		i;
	int		varlen;
	int		len;
	int		start;
	char	*str;

	i = 0;
	varlen = ft_strlen(var) + 1;
	var = ft_strjoin(var, "=");
	while (copyenvp[i])
	{
		if (ft_strnstr(copyenvp[i], var, varlen) != NULL)
		{
			start = ft_strlenequal(copyenvp[i]) + 1;
			len = ft_strlen(copyenvp[i]) - varlen;
			str = ft_substr(copyenvp[i], start, len);
			free(var);
			return (str);
		}
		i++;
	}
	free(var);
	return (NULL);
}
