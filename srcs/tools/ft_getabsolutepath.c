/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getabsolutepath.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 14:12:13 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/10 13:54:04 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pathsplit(char **cmd, char **path_split, char *path, char *bin)
{
	int		id;
	int		i;

	path_split = ft_split(path, ':');
	free(path);
	i = 0;
	while (path_split[i])
	{
		bin = (char *)ft_calloc(sizeof(char), (ft_strlen(path_split[i]) +
				ft_strlen(cmd[0]) + 2));
		if (bin == NULL)
			break ;
		ft_strcat(bin, path_split[i]);
		ft_strcat(bin, "/");
		ft_strcat(bin, cmd[0]);
		id = open(bin, O_RDONLY);
		if (id > 0)
			break ;
		free(bin);
		bin = NULL;
		i++;
	}
	ft_freetab(path_split);
	if (bin != NULL)
	{
		ft_delete(&cmd[0]);
		cmd[0] = bin;
	}
}

int		ft_getabsolutepath(char **cmd, t_struct *st)
{
	char	*path;
	char	*bin;
	char	**path_split;
	int		i;

	path = ft_getenv(st->copyenvp, "PATH");
	bin = NULL;
	path_split = NULL;
	i = 0;
	if (path == NULL)
	{
		ft_printf("minishell: ls: No such file or directory\n");
		free(path);
		return (0);
	}
	else if (cmd[0][0] != '/' && strncmp(cmd[0], "./", 2) != 0)
		ft_pathsplit(cmd, path_split, path, bin);
	else
		free(path);
	return (1);
}
