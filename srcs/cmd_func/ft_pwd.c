/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:43:17 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/08 17:24:36 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_saveoldpwd(t_struct *st)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	getcwd(cwd, sizeof(cwd));
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	ft_exportenv(oldpwd, st);
	ft_delete(&oldpwd);
}

void		ft_savepwd(t_struct *st)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	st->pwd = ft_strjoin("PWD=", cwd);
	ft_exportenv(st->pwd, st);
}

int			ft_builtinpwd(t_struct *st)
{
	char cwd[PATH_MAX];

	ft_redirectbuiltin(st);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		st->envi = ft_strjoin("PWD=", cwd);
		ft_exportenv(st->envi, st);
		ft_printf("%s\n", cwd);
		ft_delete(&st->envi);
	}
	else
		ft_printf("getcwd()");
	ft_comebacktostdout(st);
	return (g_exitstatus = EXIT_SUCCESS);
}
