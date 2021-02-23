/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:16:51 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/23 15:39:05 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			ft_reset_mi(t_mini *mi)
{
	mi->error = 0;
	mi->tab_pipe = 0;
	mi->quote = 0;
	mi->nquote = 0;
	mi->islast = 0;
	mi->op = 0;
	mi->semi = 0;
	mi->fd = 1;
	if (mi->tab_arg)
		ft_free_tab(mi->tab_arg);
	ft_delete(&mi->line);
}

void			ft_free_mi(t_mini *mi)
{
	ft_delete(&mi->line);
	ft_free_tab(mi->tab_arg);
}

void			change_real_char(t_mini *mi, size_t n, size_t i)
{
	while (mi->tab_arg[n])
	{
		i = 0;
		while (mi->tab_arg[n][i])
		{
			if (mi->tab_arg[n][i] == '"' || mi->tab_arg[n][i] == '\'')
				i = ft_change_char(mi->tab_arg[n][i], mi, i + 1, n);
			else
				i++;
			if (i >= ft_strlen(mi->tab_arg[n]))
				break ;
		}
		n++;
	}
}

size_t			advance(char *str, size_t i, char c)
{
	while (str[i] && str[i] != c)
	{
		i++;
		if (str[i] == '\0')
			break ;
	}
	if (str[i] == c)
		i++;
	return (i);
}
