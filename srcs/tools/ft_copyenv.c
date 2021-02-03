/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copyenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:38:31 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/03 17:29:42 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_copyenv(char **envp)
{
	char	**tmp;
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 1)); // TODO <- free
	i = 0;
	while (envp[i] != NULL)
	{
		tmp[i] = ft_strdup(envp[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}
