/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtincd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:43:02 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/12 12:15:04 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// TODO free le trim

void		ft_cdwithargs(char **built_in, t_struct *st)
{
	built_in[1] = ft_strtrim(built_in[1], "\"'");
	if (ft_strcmp(built_in[1], "~") == 0)
	{
		ft_saveoldpwd(st);
		built_in[1] = ft_strdup(ft_getenv(st->copyenvp, "HOME"));
	}
	else if (ft_strcmp(built_in[1], "-") == 0)
	{
		if (!ft_getenv(st->copyenvp, "OLDPWD"))
			ft_printf("cd: « OLDPWD » non défini");
		else
		{
			ft_printf("%s\n", ft_strdup(ft_getenv(st->copyenvp, "OLDPWD")));
			built_in[1] = ft_strdup(ft_getenv(st->copyenvp, "OLDPWD"));
		}
	}
	// else if (ft_strchr(built_in[1], '$'))
	// 	built_in[1] = ft_strdup(ft_getenv(st->copyenvp, (ft_strtrim(built_in[1], "$"))));
	ft_saveoldpwd(st);
	ft_builtincd(built_in[1], st);
}

int		ft_builtincd(char *path, t_struct *st)
{
	if (chdir(path) == -1)
	{
		ft_printf("cd: %s: No such file or directory\n", path);
		return (st->exitstatus = EXIT_FAILURE);
	}
	ft_savepwd(st);
	return (st->exitstatus = EXIT_SUCCESS);
}
