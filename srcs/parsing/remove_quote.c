/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:38:39 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/01 13:51:50 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char				*refund_quote_char(char *cmd, size_t i)
{
	while (cmd[i])
	{
		if (cmd[i] == -6)
			cmd[i] = '\"';
		if (cmd[i] == -7)
			cmd[i] = '\'';
		i++;
	}
	return (cmd);
}

static size_t			count_quote(char *str, size_t i, size_t count)
{
	while (str[i])
	{
		if (str[i] == '"' || str[i] == 39)
		{
			i = advance(str, i + 1, str[i]);
			count++;
		}
		else
			i++;
	}
	return (count);
}

static char				*str_wt_qt(char *cmd, size_t i, size_t j)
{
	size_t	count;
	size_t	k;
	char	*tmp;

	count = count_quote(cmd, 0, 0);
	tmp = malloc(sizeof(char) * (ft_strlen(cmd) - count + 1));
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
		{
			k = i + 1;
			i = advance(cmd, i + 1, cmd[i]);
			while (k < i - 1)
			{
				tmp[j] = cmd[k];
				j++;
				k++;
				if (k > i - 2)
					break ;
			}
		}
		else
		{
			tmp[j] = cmd[i];
			i++;
			j++;
		}
	}
	tmp[j] = '\0';
	free(cmd);
	return (tmp);
}

char					**remove_quote(char **cmd, size_t n)
{
	while (cmd[n])
	{
		cmd[n] = str_wt_qt(cmd[n], 0, 0);
		cmd[n] = refund_quote_char(cmd[n], 0);
		n++;
	}
	cmd[n] = NULL;
	return (cmd);
}
