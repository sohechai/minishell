/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 09:23:36 by aurelienbuc       #+#    #+#             */
/*   Updated: 2021/03/12 16:32:12 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int		ft_wordcount(const char *str, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (str[i] == '\0')
		return (n);
	while (str[i] == c)
		i++;
	if (str[i] == '\0')
		return (n);
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			while (str[i] == c)
				i++;
			if (str[i] != '\0')
				n++;
		}
		if (str[i] != '\0')
			i++;
	}
	return (n + 1);
}

static int		ft_size(int i, const char *str, char c)
{
	int	n;

	n = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		n++;
		i++;
	}
	return (n);
}

static char		**ft_crea_tab(const char *str, char **tab, char c, int i)
{
	int	j;
	int	l;
	int	v;

	j = 0;
	while (str[i])
	{
		l = 0;
		while (str[i] == c)
			i++;
		if (!(tab[j] = (char*)malloc(sizeof(char) * (ft_size(i, str, c) + 1))))
			return (ft_free_tab(tab));
		v = i;
		while (i < (v + ft_size(v, str, c)))
			tab[j][l++] = str[i++];
		tab[j][l] = '\0';
		if (j < ft_wordcount(str, c))
			j++;
	}
	tab[j] = NULL;
	return (tab);
}

char			**ft_split(char const *str, char c)
{
	char	**tab;
	int		i;

	i = 0;
	if (!(tab = (char**)malloc(sizeof(char*) * (ft_wordcount(str, c) + 1))))
		return (NULL);
	tab = ft_crea_tab(str, tab, c, i);
	return (tab);
}
