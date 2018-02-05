/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:17:37 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/10 10:05:16 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*un_decim(t_flags flags, char *str, va_list list)
{
	char	*tmp;

	tmp = str;
	if (flags.letter == 'U')
		str = ft_untoa(va_arg(list, unsigned long), flags.apo);
	else if (flags.z)
		str = ft_untoa(va_arg(list, size_t), flags.apo);
	else if (flags.j)
		str = ft_untoa(va_arg(list, uintmax_t), flags.apo);
	else if (flags.ll)
		str = ft_untoa(va_arg(list, unsigned long long), flags.apo);
	else if (flags.l)
		str = ft_untoa(va_arg(list, unsigned long), flags.apo);
	else if (flags.h)
		str = ft_untoa((unsigned short)va_arg(list, unsigned int), flags.apo);
	else if (flags.hh)
		str = ft_untoa((unsigned char)va_arg(list, unsigned int), flags.apo);
	else
		str = ft_untoa(va_arg(list, unsigned int), flags.apo);
	ft_strdel(&tmp);
	return (str);
}

static char	*decim(t_flags flags, char *str, va_list list)
{
	char	*tmp;

	tmp = str;
	if (flags.letter == 'D')
		str = ft_ltoa(va_arg(list, long), flags.apo);
	else if (flags.z)
		str = ft_ltoa(va_arg(list, ssize_t), flags.apo);
	else if (flags.j)
		str = ft_ltoa(va_arg(list, intmax_t), flags.apo);
	else if (flags.ll)
		str = ft_ltoa(va_arg(list, long long), flags.apo);
	else if (flags.l)
		str = ft_ltoa(va_arg(list, long), flags.apo);
	else if (flags.h)
		str = ft_ltoa((short)va_arg(list, int), flags.apo);
	else if (flags.hh)
		str = ft_ltoa((char)va_arg(list, int), flags.apo);
	else
		str = ft_ltoa(va_arg(list, int), flags.apo);
	ft_strdel(&tmp);
	return (str);
}

static char	*ft_prec_d(t_flags flags, char *str)
{
	char	*new_string;
	int		i;
	char	*tmp;

	if (!(new_string = ft_strnew(flags.precision - ft_strlen(str))))
		return (NULL);
	i = -1;
	while (++i < flags.precision - ft_strlen(str))
		new_string[i] = '0';
	if (ft_strchr(str, '-') || (!ft_strchr(str, '-') && flags.plus))
	{
		tmp = new_string;
		if (flags.plus)
			new_string = ft_strjoin("+", new_string);
		else if ((str[0] = '0'))
			new_string = ft_strjoin("-", new_string);
		ft_strdel(&tmp);
	}
	tmp = str;
	str = ft_strjoin(new_string, str);
	ft_strdel(&new_string);
	ft_strdel(&tmp);
	return (str);
}

char		*ft_width_d(t_flags flags, char *str)
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
	if (ft_strchr(str, '-') && flags.zero && !flags.minus && !flags.precision
		&& (str[0] = '0'))
		new_string[0] = '-';
	tmp = str;
	str = flags.minus ? ft_strjoin(str, new_string)
		: ft_strjoin(new_string, str);
	ft_strdel(&tmp);
	ft_strdel(&new_string);
	return (str);
}

int			ft_handle_d(t_flags flags, char **str, va_list list)
{
	char	*tmp;

	flags = ft_check_flags_d(flags, *str);
	if (flags.letter == 'd' || flags.letter == 'i' || flags.letter == 'D')
		*str = decim(flags, *str, list);
	else if (flags.letter == 'u' || flags.letter == 'U')
		*str = un_decim(flags, *str, list);
	if (flags.point && *str[0] == '0' && ft_strlen(*str) == 1)
		ft_strclr(*str);
	if (flags.precision >= ft_strlen(*str))
		*str = ft_prec_d(flags, *str);
	if (flags.width > ft_strlen(*str))
		*str = ft_width_d(flags, *str);
	if (!ft_strchr(*str, '-'))
		*str = ft_handle_d_positive(flags, *str);
	if (flags.plus && !ft_strchr(*str, '+') && !ft_strchr(*str, '-'))
	{
		tmp = *str;
		*str = ft_strjoin("+", *str);
		*str = str_put_zero(*str, ft_strlen(*str) - 1);
		ft_strdel(&tmp);
	}
	return (ft_strlen(*str));
}
