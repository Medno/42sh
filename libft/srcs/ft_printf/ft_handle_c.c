/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:54:22 by kyazdani          #+#    #+#             */
/*   Updated: 2017/12/08 18:35:09 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_width_c(t_flags flags, char *str, int len)
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
		str = ft_str_join(str, new_string, len, flags.width - len);
	else
		str = ft_str_join(new_string, str, flags.width - len, len);
	ft_strdel(&tmp);
	ft_strdel(&new_string);
	return (str);
}

int		handle_wchar_ret(wint_t c)
{
	if (c >= 0xD800 && c <= 0xDFFF)
		return (-1);
	else if (c <= 127 || (c <= 255 && MB_CUR_MAX == 1))
		return (1);
	else if (c >= 0x80 && c <= 0x7FF && MB_CUR_MAX >= 2)
		return (2);
	else if (c > 0x7FF && c <= 0xFFFF && MB_CUR_MAX >= 3)
		return (3);
	else if (c > 0xFFFF && MB_CUR_MAX == 4)
		return (4);
	else
		return (-1);
}

int		handle_wchar_ret_nocurmax(wint_t c)
{
	if (c >= 0xD800 && c <= 0xDFFF)
		return (-1);
	else if (c <= 127 || (c <= 255 && MB_CUR_MAX == 1))
		return (1);
	else if (c >= 0x80 && c <= 0x7FF)
		return (2);
	else if (c > 0x7FF && c <= 0xFFFF)
		return (3);
	else if (c > 0xFFFF)
		return (4);
	else
		return (-1);
}

char	*ft_convert_wct(wint_t c)
{
	int		len;
	char	*str;

	len = handle_wchar_ret(c);
	str = ft_strnew(len);
	if (c <= 0x7F || (c <= 255 && MB_CUR_MAX == 1))
		str[len - 1] = (char)c;
	else if (MB_CUR_MAX > 1 && c >= 0x80 && (str[len - 1] = (char)((0x3F & c)
				| 0x80)))
	{
		if (c >= 0x80 && c <= 0x7FF && MB_CUR_MAX >= 2)
			str[len - 2] = (char)((((0x7C0 & c) << 2) | 0xC080) >> 8);
		else
		{
			str[len - 2] = (char)((((0xFC0 & c) << 2) | 0x8080) >> 8);
			if (c >= 0x800 && c <= 0xFFFF && MB_CUR_MAX >= 3)
				str[len - 3] = (char)((((0xF000 & c) << 4) | 0xE08080) >> 16);
			else if (c >= 0x10000 && c <= 0x1FFFFF && MB_CUR_MAX == 4 &&
					(str[len - 4] = (char)((((0x1C0000 & c) << 6)
					| 0xF0808080) >> 24)))
				str[len - 3] = (char)((((0x3F000 & c) << 4) | 0x808080) >> 16);
		}
	}
	return (str);
}

int		ft_handle_c(t_flags flags, char **str, va_list list)
{
	int		content;
	char	*tmp;

	content = va_arg(list, int);
	ft_strclr(*str);
	if (flags.letter == 'C' || flags.l)
	{
		tmp = *str;
		*str = ft_convert_wct((wint_t)content);
		ft_strdel(&tmp);
		if (flags.width > handle_wchar_ret(content) && flags.width)
		{
			*str = handle_width_cs(flags, *str, handle_wchar_ret(content));
			return (flags.width);
		}
		return (handle_wchar_ret(content));
	}
	else
		*str[0] = (unsigned char)content;
	if (flags.width > 1)
	{
		*str = handle_width_c(flags, *str, 1);
		return (flags.width);
	}
	return (1);
}
