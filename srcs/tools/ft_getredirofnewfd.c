/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getredirofnewfd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 18:01:56 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/13 18:02:03 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			ft_getredirofnewfd(char *files, t_struct *st)
{
	int		len;

	len = ft_strlen(files);
	if (ft_strchr(files, '<'))
	{
		if (!ft_strchr(files, '>'))
			st->redirection = LEFTRED;
		st->leftredir = 1;
	}
	while (len > 0)
	{
		if (files[len] == '>')
		{
			len--;
			if (files[len] == '>')
				st->redirection = DOUBLERED;
			else
				st->redirection = SIMPLERED;
		}
		len--;
	}
}

static void		getnewfd_loop(t_struct *st, char *src, int len, int start)
{
	int		length;

	length = ft_strlen(src);
	while (len > 0)
	{
		if (src[len] == ' ')
		{
			len--;
			if (src[len] == '>' || src[len] == '<')
			{
				len = length;
				break ;
			}
			else
			{
				len--;
				break ;
			}
		}
		len--;
	}
	if (len == 0)
		len = length;
	ft_delete(&st->newfd);
	st->newfd = ft_substr(src, start, len);
}

void			ft_getnewfd(char *src, t_struct *st)
{
	int		len;
	int		start;

	len = 0;
	start = 0;
	while (src[len])
	{
		if (src[len] == '>' || src[len] == '<')
		{
			start = len;
			break ;
		}
		len++;
	}
	len = ft_strlen(src);
	getnewfd_loop(st, src, len, start);
}
