/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sohechai <sohechai@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/04 17:25:25 by sohechai     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/08 20:28:43 by sohechai    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_len_until_n(const char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (count);
		count++;
		i++;
	}
	return (count);
}

int			get_next_line(int fd, char **line)
{
	int			ret;
	static char	*str = NULL;
	char		*tmp;
	char		buf[BUFFER_SIZE + 1];

	if (!(line) || fd < 0 || BUFFER_SIZE < 1 || (read(fd, NULL, 0) < 0))
		return (-1);
	if (!(str))
		str = ft_strdup("");
	while (!(ft_strchr(str, '\n')) && (ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		str = ft_strjoin(str, buf);
	}
	if (!(ft_strchr(str, '\n')))
	{
		*line = ft_strdup(str);
		free(str);
		return (0);
	}
	if (ft_strchr(str, '\n'))
	{
		*line = ft_substr(str, 0, ft_len_until_n(str));
		tmp = ft_strdup(str + (ft_len_until_n(str) + 1));
		free(str);
		str = tmp;
		return (1);
	}
	return (-1);
}
