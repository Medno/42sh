/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_base_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 11:18:03 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/10 10:05:48 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_handle_hash(t_flags flags, char *str)
{
	char	*tmp;

	if (!(ft_strlen(str) == 1 && str[0] == '0') || flags.letter == 'p')
	{
		if (ft_strlen(str) == 1 && str[0] == '0' && flags.letter == 'p'
				&& flags.point && !flags.precision)
			ft_strclr(str);
		tmp = str;
		if ((flags.letter == 'x' && flags.hash) || flags.letter == 'p')
		{
			str = ft_strjoin("0x", str);
			ft_strdel(&tmp);
		}
		else if (flags.letter == 'X' && flags.hash)
		{
			str = ft_strjoin("0X", str);
			ft_strdel(&tmp);
		}
		else if (flags.hash && !flags.precision)
		{
			str = ft_strjoin("0", str);
			ft_strdel(&tmp);
		}
	}
	return (str);
}

char	*ft_width_base(t_flags flags, char *str, char c)
{
	char	*new_string;
	int		i;
	char	*tmp;

	i = -1;
	if (!(new_string = ft_strnew(flags.width - ft_strlen(str))))
		return (NULL);
	tmp = str;
	if (flags.zero)
		while (++i < flags.width - ft_strlen(str))
			new_string[i] = '0';
	else
		while (++i < flags.width - ft_strlen(str))
			new_string[i] = ' ';
	if (flags.zero && !flags.minus && ft_strchr("xXp", c) && flags.hash)
	{
		new_string[1] = c;
		str[1] = '0';
	}
	if (flags.minus || (flags.letter == 'p' && flags.zero))
		str = ft_strjoin(str, new_string);
	else
		str = ft_strjoin(new_string, str);
	ft_strdel(&tmp);
	return (str);
}
