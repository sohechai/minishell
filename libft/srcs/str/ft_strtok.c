/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 17:08:31 by user42            #+#    #+#             */
/*   Updated: 2021/03/12 16:32:12 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

size_t		ft_strspn(char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (ft_strchr(s2, s1[i]))
		i++;
	return (i);
}

size_t		ft_strcspn(char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (!ft_strchr(s2, s1[i]))
		i++;
	return (i);
}

char		*ft_strtok(char *s, const char *charset)
{
	char			*end;
	static char		*save_str;

	if (s == NULL)
		s = save_str;
	if (*s == '\0')
	{
		save_str = s;
		return (NULL);
	}
	s += ft_strspn(s, charset);
	if (*s == '\0')
	{
		save_str = s;
		return (NULL);
	}
	end = s + ft_strcspn(s, charset);
	if (*end == '\0')
	{
		save_str = end;
		return (s);
	}
	*end = '\0';
	save_str = end + 1;
	return (s);
}
