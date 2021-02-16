/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:16:51 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/16 12:09:10 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_mini			*ft_init_mini(void)
{
	t_mini *mi;

	if (!(mi = malloc(sizeof(t_mini))))
		return (0);
	mi->echo = NULL;
	mi->line = NULL;
	mi->tab_arg = NULL;
	mi->tab_pipe = NULL;
	mi->cmd = NULL;
	mi->semi = 0;
	mi->islast = 0;
	mi->op = 0;
	mi->nquote = 0;
	mi->fd = 1;
	return (mi);
}

void			ft_reset_mi(t_mini *mi)
{
	mi->echo = NULL;
	mi->line = NULL;
	mi->tab_arg = NULL;
	mi->cmd = NULL;
	mi->semi = 0;
	mi->islast = 0;
	mi->op = 0;
	mi->nquote = 0;
	mi->fd = 1;
	ft_delete(&mi->line);
}

void			ft_free_mi(t_mini *mi)
{
	ft_delete(&mi->line);
	ft_free_tab(mi->tab_arg);
	ft_free_tab(mi->cmd);
}

void			change_real_char(t_mini *mi, size_t n, size_t i)
{
	while (mi->tab_arg[n])
	{
		while (mi->tab_arg[n][i])
		{
			if (mi->tab_arg[n][i] == '"' || mi->tab_arg[n][i] == '\'')
				i = ft_change_char(mi->tab_arg[n][i], mi, i + 1, n);
			else
				i++;
		}
		n++;
	}
}

size_t			advance(char *str, size_t i, char c)
{
	while (str[i] && str[i] != c)
	{
		if (str[i] == '\0')
			break ;
		i++;
	}
	if (str[i] == c)
		i++;
	return (i);
}
