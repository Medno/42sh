/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_c_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 09:49:50 by kyazdani          #+#    #+#             */
/*   Updated: 2017/12/08 09:51:40 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_width_cs(t_flags flags, char *str, int len)
{
	char	*new_string;
	char	*tmp;
	int		i;

	i = -1;
	if (!(new_string = ft_strnew(flags.width - len)))
		return (NULL);
	while (++i < flags.width - len)
	{
		if (!flags.zero)
			new_string[i] = ' ';
		else
			new_string[i] = '0';
	}
	tmp = str;
	if (flags.minus)
		str = ft_strjoin(str, new_string);
	else
		str = ft_strjoin(new_string, str);
	ft_strdel(&tmp);
	ft_strdel(&new_string);
	return (str);
}
