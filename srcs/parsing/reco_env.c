/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reco_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:08:40 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/01 13:50:40 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char				*recreate_str(char *str, char *env, size_t i)
{
	char	*new_str;
	char	*tmp;

	new_str = NULL;
	tmp = ft_strndup(str, i);
	tmp = ft_strfjoin(tmp, env, 3);
	new_str = ft_strfjoin(tmp, "\0", 1);
	free(str);
	return (new_str);
}

static char				*recreate_str2(char *str, char *old_str,
								char *env, size_t i, size_t j)
{
	char	*new_str;
	char	*tmp;

	new_str = NULL;
	tmp = ft_strndup(str, i);
	tmp = ft_strfjoin(tmp, env, 3);
	new_str = ft_strfjoin(tmp, old_str + j, 1);
	free(str);
	return (new_str);
}

static char				*remove_dollar(char *ostr,
								char *env, size_t i, int next)
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

int						re_env(t_struct *st, char *str, size_t i, size_t n)
{
	char	*env;
	char	*val_env;
	size_t	j;
	int		next;

	env = NULL;
	val_env = NULL;
	j = 0;
	next = 0;
	while (ft_isalnum(str[j]))
		j++;
	env = ft_strndup(str, j);
	if (!ft_getenv(st->copyenvp, env) && str[0] != '?')
	{
		if (endline(str, j))
			next = 1;
		st->tab_arg[n] = remove_dollar(st->tab_arg[n], env, i, next);
		free(env);
		return (i);
	}
	else
	{
		if (str[j] == '?')
		{
			val_env = ft_itoa(st->exitstatus);
			j++;
		}
		else
			val_env = ft_getenv(st->copyenvp, env);
		if (str[j] == '\0')
			st->tab_arg[n] = recreate_str(st->tab_arg[n], val_env, i);
		else
			st->tab_arg[n] = recreate_str2(st->tab_arg[n], str, val_env, i, j);
		return (i + j);
	}
}
