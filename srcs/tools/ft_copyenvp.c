/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copyenvp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:13:02 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/11 22:40:18 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_savelastcmd(int n, t_struct *st)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_strtokk(st->tab_arg[n], " ");
	while (tmp[i])
		i++;
	st->lastcmd = dup_and_free(st->lastcmd, tmp[i - 1]);
	ft_freetab(tmp);
}

void		create_env(t_struct *st)
{
	char	cwd[PATH_MAX];

	if (!(st->copyenvp = malloc(sizeof(char*) * (4 + 1))))
		ft_printf("failed allocated memory to envp\n");
	st->copyenvp[0] = ft_strdup("OLDPWD");
	getcwd(cwd, sizeof(cwd));
	st->copyenvp[1] = ft_strjoin("PWD=", cwd);
	st->copyenvp[2] = ft_strdup("SHLVL=1");
	st->copyenvp[3] = ft_strdup("_=/usr/bin/env");
	st->copyenvp[4] = NULL;
}

static void	copy_loop(t_struct *st, char **envp, int shlvl, int i)
{
	if (ft_strnstr(envp[i], "OLDPWD", 6))
		st->copyenvp[i] = ft_strdup("OLDPWD");
	else if (ft_strnstr(envp[i], "SHLVL", 5))
		st->copyenvp[i] = ft_strfjoin("SHLVL=", ft_itoa(shlvl), 2);
	else if (ft_strnstr(envp[i], "_=", 2))
		st->copyenvp[i] = ft_strdup("_=/usr/bin/env");
	else
		st->copyenvp[i] = ft_strdup(envp[i]);
}

void		ft_copyenvp(char **envp, t_struct *st)
{
	int		i;
	int		shlvl;
	int		len;

	i = 0;
	if ((len = ft_countenv(envp)) == 0)
		create_env(st);
	else
	{
		st->envi = ft_getenv(envp, "SHLVL");
		shlvl = ft_atoi(st->envi) + 1;
		if (!(st->copyenvp = ft_calloc(sizeof(char*), (len + 1))))
			ft_printf("failed allocate memory to envp\n");
		while (envp[i])
		{
			copy_loop(st, envp, shlvl, i);
			i++;
		}
		st->copyenvp[i] = NULL;
		ft_delete(&st->envi);
	}
	st->lastcmd = ft_getenv(st->copyenvp, "_");
}
