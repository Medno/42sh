/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 09:17:49 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/18 15:04:10 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	send_fun_2(t_flags flags, char **tab, va_list list)
{
	if (flags.letter == 'b')
		return (ft_handle_binary(flags, tab, list));
	else if (flags.letter == 'f' || flags.letter == 'F')
		return (ft_handle_f(flags, tab, list));
	else
		return (0);
}

static int	send_fun(t_flags flags, char **tab, va_list list)
{
	if (ft_strchr("cdipsu", flags.letter))
		flags.hash = 0;
	if (ft_strchr("scCpuUxXoO", flags.letter))
	{
		flags.space = 0;
		flags.plus = 0;
	}
	if (ft_strchr("douixX", flags.letter) && flags.precision)
		flags.zero = 0;
	if (flags.percent || !flags.letter)
		return (ft_handle_percent(flags, tab));
	else if (flags.letter == 'd' || flags.letter == 'D' || flags.letter == 'i'
			|| flags.letter == 'u' || flags.letter == 'U')
		return (ft_handle_d(flags, tab, list));
	else if (flags.letter == 'x' || flags.letter == 'X' || flags.letter == 'o'
			|| flags.letter == 'O' || flags.letter == 'p')
		return (ft_handle_base(flags, tab, list));
	else if (flags.letter == 's' || flags.letter == 'S')
		return (ft_handle_s(flags, tab, list));
	else if (flags.letter == 'c' || flags.letter == 'C')
		return (ft_handle_c(flags, tab, list));
	else
		return (send_fun_2(flags, tab, list));
}

int			ft_convert_str(char **str, char **array, va_list list,
		t_colors colors)
{
	int			i;
	char		*tmp;
	t_flags		flags;
	int			result;
	int			tmpsize;

	i = -1;
	result = 0;
	while (array[++i])
	{
		if (*array[i] == '%')
		{
			flags = ft_flags(array[i], list);
			if ((tmpsize = send_fun(flags, &array[i], list)) == -1)
				return (-1);
		}
		else
			tmpsize = handle_color(&array[i], colors);
		tmp = *str;
		*str = ft_str_join(*str, array[i], result, tmpsize);
		ft_strdel(&tmp);
		result = result + tmpsize;
	}
	return (result);
}
