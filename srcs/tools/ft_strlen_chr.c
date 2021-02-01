/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_chr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Tcurinie <tcurinie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:58:02 by Tcurinie          #+#    #+#             */
/*   Updated: 2021/01/08 16:06:00 by Tcurinie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strlen_chr(char *str, int c)
{
	int i;

	i = 0;
	while (str)
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return(ERROR);
}