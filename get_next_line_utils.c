/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sohechai <sohechai@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/04 17:42:54 by sohechai     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/18 15:58:45 by sohechai    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char		*ft_strdup(const char *src)
{
	char	*dest;
	int		length;
	int		i;

	i = 0;
	length = ft_strlen(src);
	if (!(dest = malloc(sizeof(char) * (length) + 1)))
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char		*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	char	*dest;

	i = 0;
	size = ft_strlen(s);
	if (!(dest = malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (len != 0 && start < size)
	{
		dest[i] = s[start];
		start++;
		i++;
		len--;
	}
	dest[i] = '\0';
	return (dest);
}

char		*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (c == s[i])
			return ((char*)s + i);
		s++;
	}
	if (c == '\0' && s[i] == '\0')
		return ((char*)s);
	return (NULL);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*dest;
	size_t	i;
	size_t	j;
	size_t	k;

	len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	k = 0;
	if (!(dest = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (s1[i])
		dest[k++] = s1[i++];
	while (s2[j])
		dest[k++] = s2[j++];
	dest[k] = '\0';
	free((char*)s1);
	return (dest);
}
