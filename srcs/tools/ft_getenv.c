/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:59:54 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/12 11:42:54 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// gcc -Wall -Wextra -Werror -L libft/ -lft srcs/tools/ft_getenv.c && ./a.out

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

char		*ft_getenv(char **envp, char *var)
{
	int		i;
	int		varlen;
	int		len;
	int		start;
	char	*str;

	i = 0;
	varlen = ft_strlen(var) + 1;
	var = ft_strjoin(var, "=");
	while (envp[i])
	{
		if (ft_strnstr(envp[i], var, varlen) != NULL)
		{
			start = ft_strlenequal(envp[i]) + 1;
			len = ft_strlen(envp[i]) - varlen;
			str = ft_substr(envp[i], start, len);
			return (str);
		}
		i++;
	}
	return (NULL);
}
