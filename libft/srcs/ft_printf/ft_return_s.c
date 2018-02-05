/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 16:03:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/10 10:06:58 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_handle_return_s(wchar_t *content, t_flags flags)
{
	int		i;
	int		result;
	int		tmpresult;

	i = -1;
	result = 0;
	while (content[++i])
	{
		if ((tmpresult = handle_wchar_ret(content[i])) == -1)
			return (-1);
		if (flags.point && flags.precision < result + tmpresult)
			return (result);
		result = result + tmpresult;
	}
	return (result);
}
