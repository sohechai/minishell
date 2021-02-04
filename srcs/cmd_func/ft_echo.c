/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:10:09 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/04 15:10:14 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void		op(t_mini *mi, size_t i, size_t n)
{
//	printf("mi->line = [%s]\n", mi->line);
	while (mi->tab_arg[n][i])
	{
		if (!ft_strchr("- ", mi->tab_arg[n][i]))
			break ;
		if (mi->tab_arg[n][i] == '-' && mi->tab_arg[n][i + 1] == 'n')
		{
			mi->op = i + 2;
			break ;
		}
		i++;
	}
}

static char		*clean_bef_aft(char *str, size_t i, size_t st, size_t end)
{
	char	*tmp;

	tmp = NULL;
	if (i >= ft_strlen(str))
		return (0);
	while (ft_strchr(" \t\n\r\v\f", str[i]))
		i++;
	st = i;
	while (ft_strchr(" \t\n\r\v\f", str[end]))
		end--;
	end += 1;
	tmp = ft_strndup(str + st, end);
	ft_delete(&str);
	return (tmp);
}

static int			recover_print(t_mini *mi, size_t i, size_t n)
{
	if (!(mi->tab_arg[n] = clean_bef_aft(mi->tab_arg[n], i, 0,
			ft_strlen(mi->tab_arg[n]))))
		return (0);
	clean_spaces_bet(mi, n, 0);
	return (1);
}

static void			rechange_character(t_mini *mi, size_t i, size_t n)
{
	while (mi->tab_arg[n][i])
	{
		if (mi->tab_arg[n][i] == -1)
			mi->tab_arg[n][i] = '\\';
		if (mi->tab_arg[n][i] == -2)
			mi->tab_arg[n][i] = ';';
		if (mi->tab_arg[n][i] == -3)
			mi->tab_arg[n][i] = '|';
		if (mi->tab_arg[n][i] == -4)
			mi->tab_arg[n][i] = '>';
		if (mi->tab_arg[n][i] == -5)
			mi->tab_arg[n][i] = '<';
		if (mi->tab_arg[n][i] == -6)
			mi->tab_arg[n][i] = '\"';
		if (mi->tab_arg[n][i] == -7)
			mi->tab_arg[n][i] = '\'';
		i++;
	}
}

int					ft_echo(t_mini *mi, size_t n)
{
	size_t		i;

	i = 0;
//	dprintf(1, "{%s}\n", mi->tab_arg[0]);
	op(mi, 4, n);
//	printf("[%s]\n", mi->tab_arg[n]);
	if (!recover_print(mi, mi->op ? mi->op : 4, n))
		return (0);
	rechange_character(mi, 0, n);
	ft_printf("%s", mi->tab_arg[n]);
	if (!mi->op)
		ft_putchar('\n');
	mi->nquote = 0;
	mi->op = 0;
	return (1);
}