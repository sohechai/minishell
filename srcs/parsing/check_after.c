/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_after.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:53:53 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/05 16:01:33 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int					check_after(char *str, size_t i, char c)
{
	while (str[i] && str[i] != c)
	{
		if (ft_isascii(str[i]) && str[i] != c
			&& str[i] != ' ' && str[i] != '\t')
			return (1);
		i++;
	}
	if (str[i] == c)
		return (ft_error(';', 1));
	return (1);
}
