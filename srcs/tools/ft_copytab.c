/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copytab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:42:21 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/11 14:33:21 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char			**ft_copytabnew(char **src)
{
	char	**dest;
	int		len;
	int		i;

	len = ft_countenv(src) + 1;
	i = 0;
	if (!(dest = ft_calloc(sizeof(char*), (len + 1))))
	{
		ft_printf("failed allocate memory to envp\n");
		return (NULL);
	}
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

char			**ft_copytab(char **src)
{
	char	**dest;
	int		len;
	int		i;

	len = ft_countenv(src);
	i = 0;
	if (!(dest = ft_calloc(sizeof(char*), (len + 1))))
	{
		ft_printf("failed allocate memory to envp\n");
		return (NULL);
	}
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
	ft_freetab(src);
	return (dest);
}
