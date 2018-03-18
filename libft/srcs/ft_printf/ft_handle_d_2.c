/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_d_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 12:49:25 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/18 11:15:42 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_handle_d_positive(t_flags flags, char *str)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	if (!(i = 0) && flags.plus && !flags.precision && flags.width)
	{
		if (str[0] == '0')
			str[0] = '+';
		else
			while (!ft_isdigit(str[i]))
				i++;
		str[i - 1] = '+';
	}
	else if (flags.space && flags.width)
		str[0] = ' ';
	else if (!flags.width)
	{
		if (flags.plus && (tmp = str))
			str = ft_strjoin("+", str);
		else if (flags.space && !flags.width && (tmp = str))
			str = ft_strjoin(" ", str);
		if (tmp && (ft_strchr(str, '+') || ft_strchr(str, ' ')))
			ft_strdel(&tmp);
	}
	return (str);
}

t_flags		ft_check_flags_d(t_flags flags, char *str)
{
	int		count_p;

	count_p = 0;
	if (flags.point)
		flags.zero = 0;
	while (*str)
	{
		if (*str == '.')
			count_p++;
		str++;
	}
	if (count_p != 1)
	{
		flags.point = 0;
		flags.precision = 0;
	}
	return (flags);
}

char		*str_put_zero(char *str, int length)
{
	if (!ft_isdigit(str[ft_strlen(str) - 1]))
		str[length] = '\0';
	return (str);
}
