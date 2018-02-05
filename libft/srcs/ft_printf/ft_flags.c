/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 19:06:58 by kyazdani          #+#    #+#             */
/*   Updated: 2017/12/09 16:55:40 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_flags	ft_check_lengthspec(char *str, t_flags flags)
{
	while (*str)
	{
		if (*str == 'h' && *(str + 1) == 'h')
			flags.hh = 1;
		else if (*str == 'L')
			flags.lfd = 1;
		else if (*str == 'h' && *(str + 1) != 'h' && *(str - 1) != 'h')
			flags.h = 1;
		else if (*str == 'j')
			flags.j = 1;
		else if (*str == 'z')
			flags.z = 1;
		else if (*str == 'l' && *(str + 1) == 'l')
			flags.ll = 1;
		else if (*str == 'l' && *(str + 1) != 'l' && *(str - 1) != 'l')
			flags.l = 1;
		else if (*str == '*')
			flags.wildcard = 1;
		str++;
	}
	return (flags);
}

static t_flags	ft_check_precnwidth(char *str, t_flags flags)
{
	while (*str)
	{
		if (*str == '.')
		{
			str++;
			while (ft_isdigit(*str))
			{
				flags.precision = flags.precision * 10 + *str - '0';
				str++;
			}
		}
		else if (ft_isdigit(*str) && *str != '0')
		{
			while (ft_isdigit(*str))
			{
				flags.width = flags.width * 10 + *str - '0';
				str++;
			}
		}
		if (*str && *str != '.')
			str++;
	}
	if (flags.precision <= 0)
		flags.precision = 0;
	return (flags);
}

static t_flags	ft_conversion_flag(t_flags flags, char *str)
{
	int		letter;
	char	*converters;

	if (!(converters = ft_strdup("spdiouxcfbFSDOUXC")))
		return (flags);
	letter = ft_strcspn(converters, str);
	flags.letter = converters[letter];
	ft_strdel(&converters);
	return (flags);
}

static t_flags	ft_parse_flags(char *str, t_flags flags)
{
	str++;
	flags = ft_check_precnwidth(str, flags);
	flags = ft_check_lengthspec(str, flags);
	flags = ft_conversion_flag(flags, str);
	while (*str)
	{
		if (*str == '%')
			flags.percent = 1;
		else if (*str == '#')
			flags.hash = 1;
		else if (*str == ' ')
			flags.space = 1;
		else if (*str == '0' && !ft_isdigit(*(str - 1)))
			flags.zero = 1;
		else if (*str == '-')
			flags.minus = 1;
		else if (*str == '+')
			flags.plus = 1;
		else if (*str == '.')
			flags.point = 1;
		else if (*str == 39)
			flags.apo = 1;
		str++;
	}
	return (flags);
}

t_flags			ft_flags(char *str, va_list list)
{
	t_flags	flags;
	int		*pointe;

	pointe = &(flags.percent);
	while (pointe <= &(flags.z))
	{
		*pointe = 0;
		pointe++;
	}
	flags = ft_parse_flags(str, flags);
	if (flags.minus && flags.zero)
		flags.zero = 0;
	if (flags.plus && flags.space)
		flags.space = 0;
	if (flags.wildcard)
	{
		flags = ft_checkout_wildcard(flags, str, list);
		flags = check_prec_with_wc(flags, str);
		if (flags.precision < 0)
			flags.precision = 0;
	}
	return (flags);
}
