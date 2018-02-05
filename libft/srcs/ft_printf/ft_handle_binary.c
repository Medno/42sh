/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_binary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 18:53:51 by kyazdani          #+#    #+#             */
/*   Updated: 2017/12/08 12:12:58 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_bin_8(char n)
{
	char			*str;
	unsigned char	test;
	int				i;

	test = 128;
	i = 0;
	if (!(str = ft_strnew(8)))
		return (NULL);
	while (i < 8)
	{
		str[i] = test & n ? '1' : '0';
		test = test >> 1;
		i++;
	}
	return (str);
}

static char	*ft_bin_16(short n)
{
	char			*str;
	unsigned short	test;
	int				i;

	test = 32768;
	i = -1;
	if (!(str = ft_strnew(17)))
		return (NULL);
	while (++i < 17)
	{
		if (i == 8)
			str[i] = ' ';
		else
		{
			str[i] = test & n ? '1' : '0';
			test = test >> 1;
		}
	}
	return (str);
}

static char	*ft_bin_32(int n)
{
	char			*str;
	unsigned int	test;
	int				i;

	test = 2147483648;
	i = -1;
	if (!(str = ft_strnew(35)))
		return (NULL);
	while (++i < 35)
	{
		if (i == 8 || i == 17 || i == 26)
			str[i] = ' ';
		else
		{
			str[i] = test & n ? '1' : '0';
			test = test >> 1;
		}
	}
	return (str);
}

static char	*ft_bin_64(long long n)
{
	char				*str;
	unsigned long long	test;
	int					i;

	test = 0x8000000000000000;
	i = -1;
	if (!(str = ft_strnew(71)))
		return (NULL);
	while (++i < 71)
	{
		if (i == 8 || i == 17 || i == 26 || i == 44 || i == 53
			|| i == 62)
			str[i] = ' ';
		else if (i == 35)
			str[i] = '\n';
		else
		{
			str[i] = test & n ? '1' : '0';
			test = test >> 1;
		}
	}
	return (str);
}

int			ft_handle_binary(t_flags flags, char **str, va_list list)
{
	char	*tmp;

	tmp = *str;
	if (flags.z)
		*str = ft_bin_64(va_arg(list, unsigned long long));
	else if (flags.ll)
		*str = ft_bin_64(va_arg(list, long long));
	else if (flags.l && flags.j)
		*str = ft_bin_32(va_arg(list, unsigned int));
	else if (flags.l)
		*str = ft_bin_32(va_arg(list, int));
	else if (flags.j)
		*str = ft_bin_16((unsigned short)va_arg(list, int));
	else if (flags.h)
		*str = ft_bin_16((short)va_arg(list, int));
	else if (flags.hh)
		*str = ft_bin_8((unsigned char)va_arg(list, int));
	else
		*str = ft_bin_8((char)va_arg(list, int));
	ft_strdel(&tmp);
	return (ft_strlen(*str));
}
