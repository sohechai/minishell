/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copyenvp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:13:02 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/08 17:13:34 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_copyenvp(char **envp, t_struct *st)
{
	int		i;
	int		shlvl;
	int		len;

	i = 0;
	st->envi = ft_getenv(envp, "SHLVL");
	shlvl = ft_atoi(st->envi) + 1;
	len = ft_countenv(envp);
	ft_delete(&st->envi);
	if (!(st->copyenvp = ft_calloc(sizeof(char*), (len + 1))))
		ft_printf("failed allocate memory to envp\n");
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "OLDPWD", 6))
			st->copyenvp[i] = ft_strdup("OLDPWD");
		else if (ft_strnstr(envp[i], "SHLVL", 5))
			st->copyenvp[i] = ft_strfjoin("SHLVL=", ft_itoa(shlvl), 2);
		else
			st->copyenvp[i] = ft_strdup(envp[i]);
		i++;
	}
	st->copyenvp[i] = NULL;
	i = 0;
}
