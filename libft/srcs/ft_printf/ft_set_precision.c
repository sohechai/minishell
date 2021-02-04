/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelienbucher <aurelienbucher@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:10:07 by aurbuche          #+#    #+#             */
/*   Updated: 2020/06/03 11:30:21 by aurelienbuc      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libftprintf.h"

void			ft_set_precinext(t_op *op, size_t tmp, size_t i, char c)
{
	tmp = op->preci - tmp;
	op->rprint = malloc(sizeof(char) * (op->preci + 1));
	while (i < tmp)
	{
		op->rprint[i] = c;
		i++;
	}
	op->rprint[i] = '\0';
	op->rprint = ft_strfjoin(op->rprint, op->buffer, 1);
}

void			ft_set_precision(t_op *op)
{
	size_t		tmp;
	size_t		i;
	char		c;

	i = 0;
	tmp = ft_strlen(op->buffer);
	c = '0';
	if (op->preci > (ssize_t)tmp && op->converter != 's')
		ft_set_precinext(op, tmp, i, c);
	else if (op->preci < (ssize_t)tmp && op->converter == 's'
		&& !op->is_a_negative_precision)
	{
		op->rprint = ft_strndup(op->buffer, op->preci);
	}
	else
	{
		op->rprint = ft_strdup(op->buffer);
	}
}
