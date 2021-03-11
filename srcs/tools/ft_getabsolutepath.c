/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getabsolutepath.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 14:12:13 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/11 18:53:42 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*redup(char *del, char *ret)
{
	ft_delete(&del);
	return (ret);
}

void	ft_pathsplit(char **cmd, char **path_split, char *path, char *bin)
{
	int		id;
	int		i;

	path_split = ft_split(path, ':');
	ft_delete(&path);
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
		ft_delete(&bin);
		i++;
	}
	ft_freetab(path_split);
	if (bin != NULL)
		cmd[0] = redup(cmd[0], bin);
}

int		ft_getabsolutepath(char **cmd, t_struct *st)
{
	char	*path;
	char	*bin;
	char	**path_split;

	path = ft_getenv(st->copyenvp, "PATH");
	bin = NULL;
	path_split = NULL;
	if (path == NULL)
	{
		ft_printf("minishell: %s: No such file or directory\n", cmd[0]);
		free(path);
		return (0);
	}
	else if (cmd[0][0] != '/' && strncmp(cmd[0], "./", 2) != 0)
		ft_pathsplit(cmd, path_split, path, bin);
	else
		free(path);
	return (1);
}
