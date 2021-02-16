/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reco_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:08:40 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/16 12:08:50 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char				*recreate_str(char *str, char *env, size_t i)
{
	char	*new_str;
	char	*tmp;

	new_str = NULL;
	tmp = malloc(sizeof(char) * (i));
	tmp = ft_strncpy(tmp, str, i);
	tmp = ft_strfjoin(tmp, env, 3);
	new_str = ft_strfjoin(tmp, "\"", 1);
	free(str);
	return (new_str);
}

static char				*recreate_str2(char *str, char *old_str,
								char *env, size_t i, size_t j)
{
	char	*new_str;
	char	*tmp;

	new_str = NULL;
	tmp = malloc(sizeof(char) * (i));
	tmp = ft_strncpy(tmp, str, i);
	tmp = ft_strfjoin(tmp, env, 3);
	new_str = ft_strfjoin(tmp, old_str + j, 1);
	free(str);
	return (new_str);
}

int						re_env(t_mini *mi, char *str, size_t i, size_t n)
{
	char	*env;
	char	*val_env;
	size_t	j;

	env = NULL;
	val_env = NULL;
	j = 0;
	while (ft_isalpha(str[j]))
		j++;
	env = ft_strndup(str, j);
	if (!ft_getenv(mi->envp, env) && endline(str, j))
		return (0);
	else if (!ft_getenv(mi->envp, env))
		return (0);
	else
	{
		val_env = ft_getenv(mi->envp, env);
		if (str[j] == '\0')
			mi->tab_arg[n] = recreate_str(mi->tab_arg[n], val_env, i);
		else
			mi->tab_arg[n] = recreate_str2(mi->tab_arg[n], str, val_env, i, j);
		return (i + j);
	}
}
