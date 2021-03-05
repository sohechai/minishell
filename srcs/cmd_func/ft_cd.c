/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:43:02 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/05 15:20:29 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_cdwithargs(char **built_in, t_struct *st)
{
	// char	*env;

	// env = ft_strdup("OLDPWD");
	// built_in[1] = ft_strtrim(built_in[1], "\"'");
	if (ft_strcmp(built_in[1], "~") == 0)
	{
		ft_saveoldpwd(st);
		ft_delete(&built_in[1]);
		built_in[1] = ft_strdup(st->home);
	}
	else if (ft_strcmp(built_in[1], "-") == 0)
	{
		st->envi = ft_getenv(st->copyenvp, "OLDPWD");
		if (!st->envi)
		{
			ft_printf("minishell: cd: « OLDPWD » not set\n");
			return (0);
		}
		else
		{
			ft_redirectbuiltin(st);
			ft_printf("%s\n", st->envi);
			ft_delete(&built_in[1]);
			built_in[1] = ft_strdup(st->envi);
			ft_comebacktostdout(st);
		}
	}
	ft_saveoldpwd(st);
	ft_builtincd(built_in[1], st);
	return (1);
}

int			ft_builtincd(char *path, t_struct *st)
{
	ft_redirectbuiltin(st);
	if (chdir(path) == -1)
	{
		ft_printf("minishell: cd: %s: No such file or directory\n", path);
		return (st->exitstatus = EXIT_FAILURE);
	}
	ft_comebacktostdout(st);
	ft_savepwd(st);
	ft_delete(&st->pwd);
	return (st->exitstatus = EXIT_SUCCESS);
}
