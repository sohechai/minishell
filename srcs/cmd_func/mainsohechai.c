/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainsohechai.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:30:25 by sohechai          #+#    #+#             */
/*   Updated: 2021/01/23 19:34:33 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     main(int argc, char **argv, char **envp)
{
	t_env	*st;
	char    *buffer = NULL;
	size_t  buf_size = 2048;
	char	**cmd = NULL;
	if (argc < 1)
		return (-1);
	(void)argv;
	st->env = **envp;
	buffer = (char *)calloc(sizeof(char), buf_size);
	if (buffer == NULL)
	{
		perror("Malloc failure"); // TODO fonction non autorisée à modifier
		return (EXIT_FAILURE);
	}
	ft_printf("$> ");
	while (getline(&buffer, &buf_size, stdin) > 0)
	{
		cmd = split(buffer, " \n\t");
		if (cmd[0] == NULL)
			ft_printf(""); // TODO ft_printf
		else if (ft_is_built_in(cmd[0]) == false)
		{
			ft_getabsolutepath(cmd);
			ft_execcmd(cmd);
		}
		else
			ft_exec_built_in(cmd, st);
		ft_printf("$> ");
		ft_freetab(cmd);
	}
	ft_printf("exit\n");
	free(buffer);
}
