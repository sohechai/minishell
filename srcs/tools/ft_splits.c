/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:38:00 by sohechai          #+#    #+#             */
/*   Updated: 2021/02/01 16:11:05 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_splits(char *raw_cmd, char *limit)
{
	char	*ptr;
	char	**cmd = NULL;
	size_t	i = 0;

	ptr = strtok(raw_cmd, limit);
	while (ptr)
	{
		cmd = (char **)realloc(cmd, ((i + 1) * sizeof(char *)));
		cmd[i] = ft_strdup(ptr);
		ptr = strtok(NULL, limit); // TODO ft strtok
		++i;
	}
	cmd = (char **)realloc(cmd, ((i + 1) * sizeof(char *)));
	cmd[i] = NULL;
	return (cmd);
}
