/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkpipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:45:34 by sohechai          #+#    #+#             */
/*   Updated: 2021/02/04 13:35:37 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <limits.h>
#include <signal.h>

// void    ft_checkpipe(char **argv)
// {
// 	int i;

// 	i = 0;
// 	while (argv[i])
// 	{
// 		printf("cmd = %s\n", argv[i]);
// 		i++;
// 	}
// }

// int     main(int argc, char **argv)
// {
// 	char    *buffer = NULL;
// 	size_t  buf_size = 2048;
// 	char	**cmd = NULL;
// 	int		i;
// 	buffer = (char *)ft_calloc(sizeof(char), buf_size);
// 	(void)argv;
// 	if (buffer == NULL)
// 	{
// 		perror("Malloc failure"); // TODO fonction non autorisée à modifier / recoder perror avec errno
// 		return (EXIT_FAILURE);
// 	}
// 	ft_printf("\033[0;34mMinishell$> \e[00m");
// 	while (getline(&buffer, &buf_size, stdin) > 0)
// 	{
// 		printf("%s", buffer);
// 		ft_printf("\033[0;34mMinishell$> \e[00m");
// 		// ft_checkpipe(argv);
// 	}
// 	ft_printf("exit\n");
// 	free(buffer);
// 	if (argc < 1)
// 		return (0);
// 	return (0);
// }
