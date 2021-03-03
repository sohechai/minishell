/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:10:53 by sohechai          #+#    #+#             */
/*   Updated: 2021/03/03 15:50:57 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			ft_exportloop(char **built_in, t_struct *st)
{
	st->i = 1;
	// built_in[st->i] = ft_strtrim(built_in[st->i], "\"'");
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

char			**ft_copytabnew(char **src)
{
	char	**dest;
	int		len;
	int		i;

	len = ft_countenv(src) + 1;
	i = 0;
	if (!(dest = ft_calloc(sizeof(char*), (len + 1))))
		ft_printf("failed allocate memory to envp\n");
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

char			**ft_copytab(char **src)
{
	char	**dest;
	int		len;
	int		i;

	len = ft_countenv(src);
	i = 0;
	if (!(dest = ft_calloc(sizeof(char*), (len + 1))))
		ft_printf("failed allocate memory to envp\n");
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

int				ft_sortvar(char *var, t_struct *st)
{
	int		i;
	char	**saveenvp;

	i = 0;
	saveenvp = ft_copytabnew(st->copyenvp);
	ft_freetab(st->copyenvp);
	if (ft_checkvarisok(var) == 1)
	{
		while (saveenvp[i] != NULL)
			i++;
		saveenvp[i] = ft_strdupwithoutquote(var);
		// free(var);
		i++;
		saveenvp[i] = NULL;
		st->copyenvp = ft_copytab(saveenvp);
		ft_freetab(saveenvp);
	}
	else
	{
		ft_printf("minishell: export: `%s': not a valid identifier\n", var);
		// free(var);
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
	if(index == -2)
		return (0);
	else if (index != -1)
	{
		free(st->copyenvp[index]);
		st->copyenvp[index] = ft_strdup(var);
	}
	else
		ft_sortvar(var, st);
	return (EXIT_SUCCESS);
}
