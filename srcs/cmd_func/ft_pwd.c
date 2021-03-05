/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:43:17 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/05 15:56:57 by sofiahechai      ###   ########lyon.fr   */
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
	//char	*pwd;

	getcwd(cwd, sizeof(cwd));
	st->pwd = ft_strjoin("PWD=", cwd);
	ft_exportenv(st->pwd, st);
	//free(pwd);
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
	return (exitstatus = EXIT_SUCCESS);
}
