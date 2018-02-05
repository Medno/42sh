/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 23:01:12 by kyazdani          #+#    #+#             */
/*   Updated: 2017/12/08 12:54:11 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_width_f(t_flags flags, char *str)
{
	char	*tmp;
	char	*new_string;
	int		i;

	i = -1;
	if (!(new_string = ft_strnew(flags.width - ft_strlen(str))))
		return (NULL);
	if (flags.zero)
		while (++i < flags.width - ft_strlen(str))
			new_string[i] = '0';
	else
		while (++i < flags.width - ft_strlen(str))
			new_string[i] = ' ';
	if (ft_strchr(str, '-') && flags.zero && (str[0] = '0'))
		new_string[0] = '-';
	if (!ft_strchr(str, '-') && flags.zero && flags.plus && (str[0] = '0'))
		new_string[0] = '+';
	tmp = str;
	str = flags.minus ? ft_strjoin(str, new_string)
		: ft_strjoin(new_string, str);
	ft_strdel(&tmp);
	ft_strdel(&new_string);
	return (str);
}

int			ft_handle_f(t_flags flags, char **str, va_list list)
{
	char	*tmp;
	int		len;

	tmp = *str;
	if (flags.point)
		len = flags.precision;
	else
		len = 6;
	if (flags.lfd)
		*str = ft_ldtoa(va_arg(list, long double), len, flags.apo);
	else
		*str = ft_dtoa(va_arg(list, double), len, flags.apo);
	ft_strdel(&tmp);
	if (flags.plus && !ft_strchr(*str, '-'))
		*str = ft_strjoin("+", *str);
	if (flags.width > ft_strlen(*str))
		*str = ft_width_f(flags, *str);
	return (ft_strlen(*str));
}
