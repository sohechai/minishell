/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getabsolutepath.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 14:12:13 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/03 12:15:19 by sofiahechai      ###   ########lyon.fr   */
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
		bin = (char *)ft_calloc(sizeof(char), (ft_strlen(path_split[i]) + ft_strlen(cmd[0]) + 2));
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
	free(cmd[0]);
	cmd[0] = bin;
}

void	ft_getabsolutepath(char **cmd, t_struct *st)
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
		path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
	if (cmd[0][0] != '/' && strncmp(cmd[0], "./", 2) != 0)
	{
		ft_pathsplit(cmd, path_split, path, bin);
		// free(path);
		// path = NULL;
	}
	else
	{
		free(path);
		//path = NULL;
	}
}
