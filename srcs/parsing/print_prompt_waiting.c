/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt_waiting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:16:34 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/01 13:49:25 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				print_prompt_waiting(t_struct *st, char *str, size_t i)
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
			st->line = ft_strfjoin(st->line, str, 2);
			ft_putstr("> ");
			continue ;
		}
		if (str[i] == '\0')
			break ;
	}
	st->line = ft_strfjoin(st->line, str, 2);
	return (1);
}
