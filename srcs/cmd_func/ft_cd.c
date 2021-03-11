/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:43:02 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/11 14:33:21 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_cdwithtild(t_struct *st, char **built_in)
{
	st->envi = ft_strfjoin("/Users/", ft_getenv(st->copyenvp, "USER"), 2);
	ft_saveoldpwd(st);
	ft_delete(&built_in[1]);
	built_in[1] = ft_strdup(st->envi);
	free(st->envi);
}

int			ft_cdwithargs(char **built_in, t_struct *st)
{
	ft_redirectbuiltin(st);
	if (ft_strcmp(built_in[1], "~") == 0)
		ft_cdwithtild(st, built_in);
	else if (ft_strcmp(built_in[1], "-") == 0)
	{
		st->envi = ft_getenv(st->copyenvp, "OLDPWD");
		if (!st->envi)
		{
			ft_comebacktostdout(st);
			ft_printf("minishell: cd: « OLDPWD » not set\n");
			free(st->envi);
			return (0);
		}
		else
		{
			ft_printf("%s\n", st->envi);
			ft_delete(&built_in[1]);
			built_in[1] = ft_strdup(st->envi);
			free(st->envi);
		}
	}
	ft_saveoldpwd(st);
	ft_builtincd(built_in[1], st);
	return (1);
}

int			ft_builtincd(char *path, t_struct *st)
{
	if (chdir(path) == -1)
	{
		ft_comebacktostdout(st);
		ft_printf("minishell: cd: %s: No such file or directory\n", path);
		return (g_exitstatus = EXIT_FAILURE);
	}
	ft_comebacktostdout(st);
	ft_savepwd(st);
	ft_delete(&st->pwd);
	return (g_exitstatus = EXIT_SUCCESS);
}
