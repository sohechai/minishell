/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 16:48:38 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/08 17:27:14 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_countenv(char **env)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

char		**ft_sortenv(char **envp)
{
	int		size;
	int		i;
	char	*tmp;
	char	**sortenv;

	size = ft_countenv(envp);
	i = 0;
	sortenv = envp;
	while (i < size - 1)
	{
		if ((ft_strcmp(envp[i], envp[i + 1])) > 0)
		{
			tmp = envp[i];
			sortenv[i] = envp[i + 1];
			sortenv[i + 1] = tmp;
			i = 0;
		}
		else
			++i;
	}
	return (sortenv);
}

void		ft_addquote(char *str)
{
	int		i;

	i = 0;
	ft_printf("declare -x ");
	while (str[i])
	{
		if (str[i] == '=')
		{
			ft_printf("=\"");
			i++;
		}
		ft_printf("%c", str[i]);
		i++;
	}
	ft_printf("\"\n");
}

char		**ft_saveenv(t_struct *st)
{
	int		i;
	int		len;
	char	**sortenv;

	i = 0;
	len = ft_countenv(st->copyenvp);
	if(!(sortenv = ft_calloc(sizeof(char*), (len + 1))))
		ft_printf("failed allocate memory to envp\n");
	while (st->copyenvp[i])
	{
		sortenv[i] = ft_strdup(st->copyenvp[i]);
		i++;
	}
	sortenv[i] = NULL;
	return(sortenv);
}

void		ft_printsortenv(t_struct *st)
{
	char	**sortquoteenv;
	char	**sortenv;
	int		i;

	sortenv = ft_saveenv(st);
	sortquoteenv = ft_sortenv(sortenv);
	i = 0;
	while (sortquoteenv[i])
	{
		if (ft_strchr(sortquoteenv[i], '=') != NULL)
		{
			ft_addquote(sortquoteenv[i]);
			i++;
		}
		else
		{
			ft_printf("declare -x %s\n", sortquoteenv[i]);
			i++;
		}
	}
}
