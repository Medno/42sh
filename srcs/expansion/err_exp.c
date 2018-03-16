/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:00:28 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/16 15:00:30 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*err_dollar(t_init *init, char *str)
{
	init->dollar = 1;
	ft_printf_fd(2, "42sh: %s: bad substitution\n", str);
	return (NULL);
}
