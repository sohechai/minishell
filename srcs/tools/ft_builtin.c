/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 14:13:27 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/12 15:01:58 by sohechai         ###   ########lyon.fr   */
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

void	ft_simplecd(t_struct *st)
{
	st->envi = ft_strfjoin("/Users/", ft_getenv(st->copyenvp, "USER"), 2);
	ft_saveoldpwd(st);
	ft_builtincd(st->envi, st);
	free(st->envi);
}

int		ft_exec_built_in(char **built_in, t_struct *st)
{
	if (!ft_strcmp(built_in[0], "pwd"))
		ft_builtinpwd(st);
	else if (!ft_strcmp(built_in[0], "cd") && built_in[1] == 0)
		ft_simplecd(st);
	else if (!ft_strcmp(built_in[0], "cd"))
		ft_cdwithargs(built_in, st);
	else if (!ft_strcmp(built_in[0], "env") && built_in[1] == NULL)
		ft_env(st->copyenvp, st);
	else if (!ft_strcmp(built_in[0], "env") && built_in[1] != NULL)
	{
		ft_printf("env: %s : No such file or directory\n", built_in[1]);
		return (g_exitstatus = 127);
	}
	else if (!ft_strcmp(built_in[0], "export") && built_in[1] == 0)
		ft_printsortenv(st, 0);
	else if (!ft_strcmp(built_in[0], "export"))
		ft_exportloop(built_in, st);
	else if (!ft_strcmp(built_in[0], "unset") && built_in[1] != 0)
		ft_unsetloop(built_in, st);
	else if (!ft_strcmp(built_in[0], "echo"))
		ft_echo(st, built_in);
	return (EXIT_SUCCESS);
}
