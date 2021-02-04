/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_character.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofiahechaichi <sofiahechaichi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:11:44 by sofiahechai       #+#    #+#             */
/*   Updated: 2021/02/04 15:12:00 by sofiahechai      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * Fonction pour changer les caracteres en caratere inexistant
 */

void			ft_change_char(char c, t_mini *mi, size_t i)
{
	if (c == ';')
		mi->line[i] = -2;
	else if (c == '|')
		mi->line[i] = -3;
	else if (c == '>')
		mi->line[i] = -4;
	else if (c == '<')
		mi->line[i] = -5;
}

/*
 * Ici on va regarder tous les carateres se trouvant entre " et ' et les remplacer
 * par des caractere non existant pour les differencier
 */

size_t			ft_check_quote(t_mini *mi, size_t i, char c)
{
	mi->quote = 1;
	while (mi->line[i] && mi->line[i] != c)
	{
		if (mi->line[i] == 34 && c == 39)
			mi->line[i] = -6;
		if (mi->line[i] == 39 && c == 34)
			mi->line[i] = -7;
		if (mi->line[i] == c)
			mi->quote = 0;
		if (ft_strchr(";|<>\\", mi->line[i]))
			ft_change_char(mi->line[i], mi, i);
		i++;
	}
	return (i);
}

/*
 * Si un caractere utilise comme condition (ex: '";|) et que celui-ci est précédé
 * d'un \ alors ce caratère devient un caratère imprimable.
 * Ici on le remplace par un caractere non existant pour le differencier
 */

void			ft_check_backslash(t_mini *mi, size_t i)
{
	while (mi->line[i])
	{
		if (mi->line[i] == '"' || mi->line[i] == '\'')
			i = ft_check_quote(mi, i + 1, mi->line[i]);
		if (mi->line[i] == '\\')
		{
			if (mi->line[i + 1] == '\\')
				str_remove_index(i, mi, -1);
			else if (mi->line[i + 1] == ';')
				str_remove_index(i, mi, -2);
			else if (mi->line[i + 1] == '|')
				str_remove_index(i, mi, -3);
			else if (mi->line[i + 1] == '>')
				str_remove_index(i, mi, -4);
			else if (mi->line[i + 1] == '<')
				str_remove_index(i, mi, -5);
			else if (mi->line[i + 1] == '\"')
				str_remove_index(i, mi, -6);
			else if (mi->line[i + 1] == '\'')
				str_remove_index(i, mi, -7);
		}
		if (mi->line[i] == '\0')
			break ;
		i++;
	}
}

/*
 * si \ est le premier caractere de la commande un multiligne
 * va se mettre pour recevoir une commande comme dans bash
 */

int				backslash(t_mini *mi)
{
	ft_putstr("> ");
	ft_delete(&mi->line);
	get_next_line(1, &mi->line);
	if (mi->line[0] == '\0')
		return (0);
	return (1);
}

/*
 * va checker les premieres pouvant être détecter
 */

int				ft_check_character(t_mini *mi)
{
	size_t i;

	i = 0;
	if (mi->line[0] == '|' || mi->line[0] == ';')
	{
		ft_error(mi->line[0], 0);
		return (0);
	}
	if (mi->line[0] == '\\' && mi->line[1] == '\0')
		if (!backslash(mi))
			return (0);
	ft_check_backslash(mi, i);
	while (mi->line[i])
	{
		if (mi->line[i] == ';' && mi->line[i + 1] == '|')
			return (ft_error('|', 1));
		if (mi->line[i] == '|' && mi->line[i + 1] == ';')
			return (ft_error(';', 1));
		i++;
	}
	if (!check_pipe(mi))
		return (0);
	return (1);
}