/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subredir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 13:08:29 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/12 14:33:17 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_getstart(char *src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		if (src[i] == '>' || src[i] == '<')
			break ;
		i++;
	}
	return (i);
}

int			ft_getend(char *src)
{
	int		end;

	end = ft_strlen(src);
	while (end > 0)
	{
		if (src[end] == ' ' || src[end] == '<' || src[end] == '>')
		{
			while (src[end] == ' ')
				end--;
			if (src[end] == '>' || src[end] == '<')
			{
				end = 0;
				break ;
			}
			else
				break ;
		}
		end--;
	}
	return (end);
}

char		*ft_subredir(char *src)
{
	int		i;
	int		j;
	int		start;
	int		end;
	char	*dest;

	i = 0;
	j = 0;
	end = ft_getend(src);
	start = ft_getstart(src);
	if (!(dest = malloc(sizeof(char) * (start + end) + 1)))
		return (NULL);
	start--;
	while (i != start)
		dest[j++] = src[i++];
	while (src[end] && end != 0)
		dest[j++] = src[++end];
	dest[j] = '\0';
	return (dest);
}
