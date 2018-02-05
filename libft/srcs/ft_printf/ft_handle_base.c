/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:19:09 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/10 10:06:06 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*base_x_str(t_flags flags, char *str, va_list list, char *base)
{
	char			*tmp;

	tmp = str;
	if (flags.letter == 'p')
		str = ft_itoa_base((unsigned long long)va_arg(list, void *), base, 16);
	else if (flags.z)
		str = ft_itoa_base(va_arg(list, size_t), base, 16);
	else if (flags.j)
		str = ft_itoa_base(va_arg(list, uintmax_t), base, 16);
	else if (flags.ll)
		str = ft_itoa_base(va_arg(list, unsigned long long), base, 16);
	else if (flags.l)
		str = ft_itoa_base(va_arg(list, unsigned long), base, 16);
	else if (flags.h)
		str = ft_itoa_base((unsigned short)va_arg(list, unsigned int),
							base, 16);
	else if (flags.hh)
		str = ft_itoa_base((unsigned char)va_arg(list, unsigned int),
							base, 16);
	else
		str = ft_itoa_base(va_arg(list, unsigned int), base, 16);
	ft_strdel(&tmp);
	return (str);
}

static char	*base_o_str(t_flags flags, char *str, va_list list, char *base)
{
	char			*tmp;

	tmp = str;
	if (flags.letter == 'O')
		str = ft_itoa_base(va_arg(list, unsigned long), base, 8);
	else if (flags.z)
		str = ft_itoa_base(va_arg(list, size_t), base, 8);
	else if (flags.j)
		str = ft_itoa_base(va_arg(list, uintmax_t), base, 8);
	else if (flags.ll)
		str = ft_itoa_base(va_arg(list, unsigned long long), base, 8);
	else if (flags.l)
		str = ft_itoa_base(va_arg(list, unsigned long), base, 8);
	else if (flags.h)
		str = ft_itoa_base((unsigned short)va_arg(list, unsigned int),
							base, 8);
	else if (flags.hh)
		str = ft_itoa_base((unsigned char)va_arg(list, unsigned int),
							base, 8);
	else
		str = ft_itoa_base(va_arg(list, unsigned int), base, 8);
	ft_strdel(&tmp);
	return (str);
}

static char	*ft_return_base(t_flags flags, char *str, va_list list)
{
	char	*base;

	if (flags.letter == 'X')
	{
		if (!(base = ft_strdup("0123456789ABCDEF")))
			return (0);
		str = base_x_str(flags, str, list, base);
		ft_strdel(&base);
	}
	else if (flags.letter == 'x' || flags.letter == 'p')
	{
		if (!(base = ft_strdup("0123456789abcdef")))
			return (0);
		str = base_x_str(flags, str, list, base);
		ft_strdel(&base);
	}
	else if (flags.letter == 'o' || flags.letter == 'O')
		str = base_o_str(flags, str, list, "01234567");
	return (str);
}

static char	*ft_prec_base(t_flags flags, char *str)
{
	char	*tmp;
	char	*new_string;
	int		i;

	i = -1;
	if (!(new_string = ft_strnew(flags.precision - ft_strlen(str))))
		return (NULL);
	tmp = str;
	while (++i < flags.precision - ft_strlen(str))
		new_string[i] = '0';
	str = ft_strjoin(new_string, str);
	ft_strdel(&new_string);
	ft_strdel(&tmp);
	return (str);
}

int			ft_handle_base(t_flags flags, char **str, va_list list)
{
	flags.zero = flags.point ? 0 : flags.zero;
	*str = ft_return_base(flags, *str, list);
	if (flags.precision > ft_strlen(*str))
		*str = ft_prec_base(flags, *str);
	*str = ft_handle_hash(flags, *str);
	if (ft_strlen(*str) == 1 && *str[0] == '0' && flags.point
			&& ((ft_strchr("oO", flags.letter) && !flags.hash)
				|| (ft_strchr("xX", flags.letter))))
		ft_strclr(*str);
	if (flags.width > ft_strlen(*str))
		*str = ft_width_base(flags, *str, flags.letter);
	return (ft_strlen(*str));
}
