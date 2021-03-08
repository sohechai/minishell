/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohechai <sohechai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:10:53 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/08 17:24:36 by sohechai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			ft_exportloop(char **built_in, t_struct *st)
{
	st->i = 1;
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
	tmp = ft_substr(var, 0, i);
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
	if (ft_strchr(src, '"'))
		length = (int)ft_strlen(src) - 2;
	else
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
	char	**saveenvp;

	i = 0;
	if (ft_checkvarisok(var) == 1)
	{
		saveenvp = ft_copytabnew(st->copyenvp);
		ft_freetab(st->copyenvp);
		while (saveenvp[i] != NULL)
			i++;
		saveenvp[i] = ft_strdupwithoutquote(var);
		i++;
		saveenvp[i] = NULL;
		st->copyenvp = ft_copytab(saveenvp);
		ft_freetab(saveenvp);
	}
	else
	{
		ft_printf("minishell: export: `%s': not a valid identifier\n", var);
		return (g_exitstatus = EXIT_FAILURE);
	}
	return (1);
}

int				ft_exportenv(char *var, t_struct *st)
{
	int		index;
	int		len;

	index = ft_checkvarismissing(var, st);
	len = ft_countenv(st->copyenvp);
	if (index == -2)
		return (0);
	else if (index != -1 && var[0] != '=')
	{
		free(st->copyenvp[index]);
		st->copyenvp[index] = ft_strdup(var);
	}
	else
		ft_sortvar(var, st);
	return (EXIT_SUCCESS);
}
