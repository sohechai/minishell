/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 14:13:27 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/04 13:58:12 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_is_built_in(char *cmd)
{
	int			i;
	const char	*built_in[] = {"pwd", "cd", "env", "echo",
								"export", "unset", NULL};

	i = 0;
	while (built_in[i])
	{
		if (ft_strcmp((char*)built_in[i], cmd) == 0)
			return (1);
		i++;
	}
	return (0);
}

int		ft_exec_built_in(char **built_in, t_struct *st)
{
	if (!ft_strcmp(built_in[0], "pwd"))
		ft_builtinpwd(st);
	else if (!ft_strcmp(built_in[0], "cd") && built_in[1] == 0)
	{
		st->envi = ft_getenv(st->copyenvp, "HOME");
		ft_saveoldpwd(st);
		ft_builtincd(st->env, st);
	}
	else if (!ft_strcmp(built_in[0], "cd"))
		ft_cdwithargs(built_in, st);
	else if (!ft_strcmp(built_in[0], "env") && built_in[1] == NULL)
		ft_env(st->copyenvp, st);
	else if (!ft_strcmp(built_in[0], "env") && built_in[1] != NULL)
	{
		ft_printf("env: %s : No such file or directory\n", built_in[1]);
		return (st->exitstatus = 127);
	}
	else if (!ft_strcmp(built_in[0], "export") && built_in[1] == 0)
		ft_printsortenv(st);
	else if (!ft_strcmp(built_in[0], "export"))
		ft_exportloop(built_in, st);
	else if (!ft_strcmp(built_in[0], "unset") && built_in[1] != 0)
		ft_unsetloop(built_in, st);
	else if (!ft_strcmp(built_in[0], "echo"))
		ft_echo(st, built_in);
	return (EXIT_SUCCESS);
}
