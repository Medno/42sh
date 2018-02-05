/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 08:20:05 by kyazdani          #+#    #+#             */
/*   Updated: 2017/12/08 10:02:42 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags		check_prec_with_wc(t_flags flags, char *str)
{
	while (*str)
	{
		if (*str == '.' && *(str + 1) == '*' && flags.precision < 0)
			flags.point = 0;
		str++;
		if (*str == '.' && *(str + 1) != '*')
			flags.point = 1;
	}
	return (flags);
}

t_flags		ft_checkout_wildcard(t_flags flags, char *str, va_list list)
{
	int		tmp;

	while (*str)
	{
		if (*str == '*')
		{
			tmp = va_arg(list, int);
			if (*(str - 1) == '.' && *(str - 2) != '0' && (flags.precision < tmp
					|| tmp < 0))
				flags.precision = tmp;
			else if (*(str + 1) == '.' && !tmp && *(str + 2) == '*'
			&& !ft_isdigit(*(str - 1)) && (flags.zero = 1))
				flags.point = 0;
			else if (*(str - 1) != '.')
			{
				if (tmp < 0 && (flags.minus = 1))
					tmp = -tmp;
				if (!ft_isdigit(*(str + 1)))
					flags.width = tmp;
			}
		}
		str++;
	}
	return (flags);
}
