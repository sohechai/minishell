/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:43:02 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/04 15:11:51 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_cdwithargs(char **built_in, t_struct *st)
{
	char	*env;

	env = ft_strdup("OLDPWD");
	// built_in[1] = ft_strtrim(built_in[1], "\"'");
	if (ft_strcmp(built_in[1], "~") == 0)
	{
		st->envi = ft_getenv(st->copyenvp, "HOME");
		ft_saveoldpwd(st);
		built_in[1] = st->envi;
	}
	else if (ft_strcmp(built_in[1], "-") == 0)
	{
		st->envi = ft_getenv(st->copyenvp, "OLDPWD");
		if (!st->envi)
		{
			ft_printf("minishell: cd: « OLDPWD » non défini");
			return (0);
		}
		else
		{
			ft_redirectbuiltin(st);
			ft_printf("%s\n", st->envi);
			built_in[1] = st->envi;
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
	return (st->exitstatus = EXIT_SUCCESS);
}
