/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:10:09 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/17 21:30:06 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char			*clean_bef_aft(char *str, size_t i, size_t st, size_t end)
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

static void			echo_loop(t_mini *mi, size_t i, size_t n)
{
	while (mi->tab_arg[n][i])
	{
		if (mi->tab_arg[n][i] == '"')
			i = print_dquote(mi, i + 1, n, '"');
		else if (mi->tab_arg[n][i] == 39)
			i = print_quote(mi, mi->tab_arg[n], i + 1);
		else
		{
			ft_putchar_fd(mi->tab_arg[n][i], mi->fd);
			i++;
		}
		if (i >= ft_strlen(mi->tab_arg[n]))
			break ;
	}
}

int					ft_echo(t_mini *mi, size_t n, t_struct *st)
{
	size_t		i;
	char		*tmp;

	i = 0;
	tmp = NULL;
	ft_redirectbuiltin(st);
	option(mi, 4, n);
	if (!recover_print(mi, mi->op ? mi->op : 4, n))
		return (0);
	rechange_character(mi, 0, n);
	echo_loop(mi, i, n);
	if (!mi->op)
		ft_putchar('\n');
	mi->nquote = 0;
	mi->op = 0;
	ft_comebacktostdout(st);
	return (1);
}