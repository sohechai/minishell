/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:16:14 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/23 15:39:05 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_error(char c, int i)
{
	if (i == 2)
	{
		ft_printf("minishell: syntax error near unexpected token"
			"\'%c%c\'\n", c, c);
		return (0);
	}
	ft_printf("minishell: syntax error near unexpected token \'%c\'\n", c);
	return (0);
}

int			endline(char *str, size_t i)
{
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

void		str_remove_index(int i, t_mini *mi, char c)
{
	char	*str;
	int		j;
	int		k;

	j = 0;
	k = 0;
	if (!(str = malloc(sizeof(char) * (ft_strlen(mi->line)))))
		exit(0);
	while (mi->line[j])
	{
		if (j != i && j != i + 1)
		{
			str[k] = mi->line[j];
			k++;
		}
		if (j == i + 1)
		{
			str[k] = c;
			k++;
		}
		j++;
	}
	str[k] = '\0';
	free(mi->line);
	mi->line = str;
}
