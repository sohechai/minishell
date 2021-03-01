/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_backslash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:53:53 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/01 13:54:41 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//static void		remove_backslash(t_struct *st, size_t i)
//{
//	while (st->line[i])
//	{
//		i++;
//	}
//}

static void		check_nbackslash(t_struct *st, size_t i)
{
	while (st->line[i])
	{
		if (st->line[i] == '\'')
			i = advance(st->line, i + 1, '\'');
		if (st->line[i] == '\\')
			st->nbackslash++;
		if (i >= ft_strlen(st->line))
			break ;
		i++;
	}
//	if ((st->nbackslash % 2) != 0)
//		remove_backslash(st,
}

int				check_backslash(t_struct *st, size_t i)
{
	check_nbackslash(st, i);
	while (st->line[i])
	{
		if (st->line[i] == '"' || st->line[i] == '\'')
			i = advance(st->line, i + 1, st->line[i]);
		if (st->line[i] == '\\')
		{
			if (st->line[i + 1] == '\\')
				str_remove_index(i, st, -1);
			else if (st->line[i + 1] == ';')
				str_remove_index(i, st, -2);
			else if (st->line[i + 1] == '|')
				str_remove_index(i, st, -3);
			else if (st->line[i + 1] == '>')
				str_remove_index(i, st, -4);
			else if (st->line[i + 1] == '<')
				str_remove_index(i, st, -5);
			else if (st->line[i + 1] == '\"')
				str_remove_index(i, st, -6);
			else if (st->line[i + 1] == '\'')
				str_remove_index(i, st, -7);
			else if (st->line[i + 1] == '$')
				st->line[i + 1] = -9;
		}
		if (st->line[i] == '\0')
			break ;
		i++;
	}
	return (1);
}
