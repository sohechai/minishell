/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt_waiting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:16:34 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/23 15:39:05 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				print_prompt_waiting(t_mini *mi, char *str, size_t i)
{
	ft_printf("> ");
	while (get_next_line(1, &str) > 0)
	{
		if (str[0] == '\0')
		{
			ft_putstr("> ");
			continue ;
		}
		if (str[0] == '|' || str[0] == ';')
			return (ft_error(str[0], 1));
		i = ft_strlen(str);
		if (str[i - 1] == '|' && str[i - 2] != '\\')
		{
			mi->line = ft_strfjoin(mi->line, str, 2);
			ft_putstr("> ");
			continue ;
		}
		if (str[i] == '\0')
			break ;
	}
	mi->line = ft_strfjoin(mi->line, str, 2);
	return (1);
}
