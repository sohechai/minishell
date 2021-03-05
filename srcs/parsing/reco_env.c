/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reco_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:08:40 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/05 15:56:57 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char		*recreate_str(t_struct *st, size_t n, size_t i)
{
	char	*new_str;
	char	*tmp;

	new_str = NULL;
	tmp = ft_strndup(st->tab_arg[n], i);
	tmp = ft_strfjoin(tmp, st->val_env, 3);
	new_str = ft_strfjoin(tmp, "\0", 1);
	ft_delete(&st->tab_arg[n]);
	return (new_str);
}

static char		*recreate_str2(t_struct *st, size_t n, size_t i, size_t j)
{
	char	*new_str;
	char	*tmp;

	new_str = NULL;
	tmp = ft_strndup(st->tab_arg[n], i);
	tmp = ft_strfjoin(tmp, st->val_env, 3);
	new_str = ft_strfjoin(tmp, st->ostr + j, 1);
	free(st->tab_arg[n]);
	return (new_str);
}

static char		*remove_dollar(char *ostr, char *env, size_t i, int next)
{
	char	*new_str;
	char	*tmp;
	size_t	j;

	new_str = NULL;
	j = i + ft_strlen(env);
	tmp = ft_strndup(ostr, i);
	if (next)
		new_str = ft_strfjoin(tmp, "\0", 1);
	else
		new_str = ft_strfjoin(tmp, ostr + (j + 1), 1);
	free(ostr);
	return (new_str);
}

static void		create_str(t_struct *st, size_t n, size_t i, size_t j)
{
	if (st->ostr[j] == '?')
	{
		st->val_env = ft_itoa(exitstatus);
		j++;
	}
	else
		st->val_env = ft_getenv(st->copyenvp, st->env);
	if (st->ostr[j] == '\0')
		st->tab_arg[n] = recreate_str(st, n, i);
	else
		st->tab_arg[n] = recreate_str2(st, n, i, j);
}

int				re_env(t_struct *st, char *str, size_t i, size_t n)
{
	size_t	j;
	int		next;

	j = 0;
	next = 0;
	st->ostr = str;
	while (ft_isalnum(str[j]))
		j++;
	st->env = ft_strndup(str, j);
	st->envi = ft_getenv(st->copyenvp, st->env);
	if (!st->envi && str[0] != '?')
	{
		if (endline(str, j))
			next = 1;
		st->tab_arg[n] = remove_dollar(st->tab_arg[n], st->env, i, next);
		ft_delete(&st->env);
		ft_delete(&st->envi);
		return (i);
	}
	else
	{
		st->tmp = str;
		create_str(st, n, i, j);
		ft_delete(&st->env);
		ft_delete(&st->envi);
		return (i + j);
	}
}
