/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtokk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 13:26:28 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/04 13:30:19 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*ft_strncpy(char *dest, char *src, unsigned int n)
// {
// 	unsigned int	i;

// 	i = 0;
// 	while (src[i] != '\0' && i < n)
// 	{
// 		dest[i] = src[i];
// 		++i;
// 	}
// 	while (i < n)
// 	{
// 		dest[i] = '\0';
// 		i++;
// 	}
// 	return (dest);
// }

static int	ft_issep(char c, char *sep)
{
	while (*sep)
	{
		if (c == *sep)
			return (1);
		sep++;
	}
	return (0);
}

static int	ft_countoken(char *str, char *sep)
{
	int		i;
	int		flag;
	int		count;

	count = 0;
	flag = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_issep(str[i], sep))
		{
			count += flag;
			flag = 0;
		}
		else
			flag = 1;
		i++;
	}
	count += flag;
	return (count);
}

static int	ft_toklen(char *str, char *sep)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && !ft_issep(str[i], sep))
		i++;
	return (i);
}

char		**ft_strtokk(char *str, char *sep)
{
	int		i;
	int		k;
	int		tok_len;
	char	**tok;

	if (!str ||
		!(tok = (char **)malloc(sizeof(char *) * (ft_countoken(str, sep) + 1))))
		return (NULL);
	i = 0;
	k = 0;
	while (k < ft_countoken(str, sep))
	{
		while (ft_issep(str[i], sep))
			i++;
		tok_len = ft_toklen(&str[i], sep);
		if (!(tok[k] = (char *)malloc(sizeof(char) * (tok_len + 1))))
			return (NULL);
		ft_strncpy(tok[k], &str[i], tok_len);
		tok[k][tok_len] = '\0';
		while (str[i] && !ft_issep(str[i], sep))
			i++;
		k++;
	}
	tok[k] = NULL;
	return (tok);
}
