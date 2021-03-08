/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_after.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:53:53 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/03/08 17:22:19 by sohechai         ###   ########lyon.fr   */
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
