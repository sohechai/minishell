/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echoutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:09:02 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/16 12:09:54 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char			*remove_spaces(t_mini *mi, char *str, size_t n, size_t tmp, size_t i)
{
	char		*s1;
	char		*s2;

	s1 = NULL;
	s2 = NULL;
	s1 = ft_strndup(mi->tab_arg[n], tmp + 1);
	while (ft_strchr(" \t\n\r\v\f", mi->tab_arg[n][i]))
		i++;
	s2 = ft_strndup(mi->tab_arg[n] + i, ft_strlen(mi->tab_arg[n]));
	str = ft_strfjoin(s1, s2, 2);
	ft_delete(&mi->tab_arg[n]);
	return (str);
}

char			*remove_quote(t_mini *mi, size_t i, size_t j, size_t n)
{
	char	*str;

	str = NULL;
	if (!(str = malloc(sizeof(char) * ft_strlen(mi->tab_arg[n]))))
		return (NULL);
	i = 0;
	while (mi->tab_arg[n][i])
	{
		if (!ft_strchr("\"", mi->tab_arg[n][i]))
		{
			str[j] = mi->tab_arg[n][i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	ft_delete(&mi->tab_arg[n]);
	return (str);
}

size_t				print_dquote(t_mini *mi, size_t i, size_t n, char c)
{
	while (mi->tab_arg[n][i] && mi->tab_arg[n][i] != c)
	{
		write(mi->fd, &mi->tab_arg[n][i], 1);
		i++;
		if (mi->tab_arg[n][i] == c)
			return (i + 1);
	}
	return (i + 1);
}

size_t				print_quote(t_mini *mi, char *str, size_t i)
{
	mi->fd = 1;
	while (str[i] && str[i] != 39)
	{
		write(mi->fd, &str[i], 1);
		i++;
		if (str[i] == '\0')
		{
			break ;
		}
	}
	return (i + 1);
}

void				clean_spaces_bet(t_mini *mi, size_t n, size_t i)
{
	char		*str;

	str = NULL;
	while (mi->tab_arg[n][i])
	{
		if (mi->tab_arg[n][i] == '"')
			i = advance(mi->tab_arg[n], i + 1, '"');
		if (i >= ft_strlen(mi->tab_arg[n]))
			break ;
		if (ft_strchr(" \t\n\r\v\f", mi->tab_arg[n][i]))
			mi->tab_arg[n] = remove_spaces(mi, str, n, i, i);
		i++;
	}
}
