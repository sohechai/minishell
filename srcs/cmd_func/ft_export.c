/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:10:53 by sohechai          #+#    #+#             */
/*   Updated: 2021/02/28 14:35:04 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			ft_exportloop(char **built_in, t_struct *st)
{
	st->i = 1;
	built_in[st->i] = ft_strtrim(built_in[st->i], "\"'");
	ft_redirectbuiltin(st);
	while (built_in[st->i] != NULL)
	{
		ft_exportenv(built_in[st->i], st);
		st->i++;
	}
	ft_comebacktostdout(st);
}

char			*ft_getvar(char *var)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	j = 0;
	len = ft_strlen(var);
	while (var[i])
	{
		if (var[i] == '=')
			break ;
		i++;
	}
	tmp = ft_substr(var, 0, i + 1);
	return (tmp);
}

char			*ft_strdupwithoutquote(const char *src)
{
	char	*dest;
	int		length;
	int		i;
	int		j;

	i = 0;
	j = 0;
	length = (int)ft_strlen(src);
	if (!(dest = malloc(sizeof(char) * (length) + 1)))
		return (NULL);
	while (src[i])
	{
		if (src[i] == '"' || src[i] == '"')
			i++;
		dest[j] = src[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

int				ft_sortvar(char *var, t_struct *st)
{
	int		i;

	i = 0;
	if (ft_checkvarisok(var) == 1)
	{
		while (st->copyenvp[i] != NULL)
			i++;
		st->copyenvp[i] = ft_strdupwithoutquote(var);
		st->copyenvp[i + 1] = NULL;
	}
	else
	{
		ft_printf("minishell: export: `%s': not a valid identifier\n", var);
		return (st->exitstatus = EXIT_FAILURE);
	}
	return (1);
}

int				ft_exportenv(char *var, t_struct *st)
{
	int		index;
	int		len;

	index = ft_checkvarismissing(var, st);
	len = ft_countenv(st->copyenvp);
	if (index != -1)
		st->copyenvp[index] = ft_strdup(var);
	else
		ft_sortvar(var, st);
	return (EXIT_SUCCESS);
}
