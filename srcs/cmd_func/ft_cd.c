/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:43:02 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/03 15:22:00 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_cdwithargs(char **built_in, t_struct *st)
{
	// built_in[1] = ft_strtrim(built_in[1], "\"'");
	if (ft_strcmp(built_in[1], "~") == 0)
	{
		ft_saveoldpwd(st);
		built_in[1] = ft_getenv(st->copyenvp, "HOME");
	}
	else if (ft_strcmp(built_in[1], "-") == 0)
	{
		if (!ft_getenv(st->copyenvp, "OLDPWD"))
			ft_printf("minishell: cd: « OLDPWD » non défini");
		else
		{
			ft_redirectbuiltin(st);
			ft_printf("%s\n", ft_getenv(st->copyenvp, "OLDPWD"));
			built_in[1] = ft_getenv(st->copyenvp, "OLDPWD");
			ft_comebacktostdout(st);
		}
	}
	ft_saveoldpwd(st);
	ft_builtincd(built_in[1], st);
}

int			ft_builtincd(char *path, t_struct *st)
{
	ft_redirectbuiltin(st);
	if (chdir(path) == -1)
	{
		ft_printf("minishell: cd: %s: No such file or directory\n", path);
		return (st->exitstatus = EXIT_FAILURE);
	}
	free(path);
	ft_comebacktostdout(st);
	ft_savepwd(st);
	return (st->exitstatus = EXIT_SUCCESS);
}
