/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exportenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:10:53 by sohechai          #+#    #+#             */
/*   Updated: 2021/02/09 17:17:07 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			ft_exportloop(char **built_in, t_struct *st)
{
	built_in[st->i] = ft_strtrim(built_in[st->i], "\"'");
	while (built_in[st->i] != NULL)
	{
		ft_exportenv(built_in[st->i], st);
		st->i++;
	}
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

char	*ft_strdupwithoutquote(const char *src)
{
	char	*dest;
	int		length;
	int		i;
	int		j;

	i = 0;
	j = 0;
	length = (int)ft_strlen(src) - 2;
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

int		ft_sortvar(char *var, t_struct *st)
{
	int		i;

	i = 0;
	if (var[0] == '$')
	{
		if (ft_getenv(st->copyenvp, ft_strtrim(var, "$")) != NULL)
			var = ft_strdup(ft_getenv(st->copyenvp, ft_strtrim(var, "$")));
		else
		{
			ft_printsortenv(st);
			return (0);
		}
	}
	if (ft_checkvarisok(var) == 1)
	{
		while (st->copyenvp[i] != NULL)
			i++;
		st->copyenvp[i] = ft_strdupwithoutquote(var);
		st->copyenvp[i + 1] = NULL;
	}
	else
		ft_printf("export: « %s » : identifiant non valable\n", var);
	return (1);
}

int			ft_exportenv(char *var, t_struct *st)
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
