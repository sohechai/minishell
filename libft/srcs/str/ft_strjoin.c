/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:05:47 by aurbuche          #+#    #+#             */
/*   Updated: 2021/03/03 12:35:02 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	ls1;
	size_t	ls2;

	if (!s1 || !s2)
		return (NULL);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	if (!(s3 = malloc(sizeof(char) * (ls1 + ls2 + 1))))
		return (NULL);
	s3 = ft_strcpy(s3, s1);
	s3 = ft_strcat(s3, s2);
	return (s3);
}
