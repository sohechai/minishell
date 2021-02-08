/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtinpwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:43:17 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/08 21:02:53 by sofiahechai      ###   ########lyon.fr   */
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
}

void		ft_savepwd(t_struct *st)
{
	char	cwd[PATH_MAX];
	char	*pwd;
	getcwd(cwd, sizeof(cwd));
	pwd = ft_strjoin("PWD=", cwd);
	ft_exportenv(pwd, st);
}

void		ft_builtinpwd(t_struct *st)
{
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_exportenv(ft_strjoin("PWD=", cwd), st);
		ft_printf("%s\n", cwd);
	}
	else
		ft_printf("getcwd()");
}
