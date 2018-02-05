/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 13:06:33 by kyazdani          #+#    #+#             */
/*   Updated: 2017/12/10 15:30:58 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**						   ==/ FT_PUTCHAR_UNICODE \==
**
**					   - This ft_putchar handle unicode -
** 	- Unicode is possible with setlocale(LC_ALL, ""); before function call -
**			- setlocale will change MB_CUR_MAX value from 1 byte to 4 -
*/

int		ft_putchar(int c)
{
	int		tmp[5];
	int		i;

	if (c >= 0x00 && c <= 0x7F && (tmp[4] = 1))
		write(1, &c, 1);
	else if (c >= 0x80 && (tmp[0] = (0x3F & c) | 0x80))
	{
		if (c >= 0x80 && c <= 0x7FF && (i = 1))
			tmp[1] = (((0x7C0 & c) << 2) | 0xC080) >> 8;
		else
		{
			tmp[1] = (((0xFC0 & c) << 2) | 0x8080) >> 8;
			if (c >= 0x800 && c <= 0xFFFF && (i = 2))
				tmp[2] = (((0xF000 & c) << 4) | 0xE08080) >> 16;
			else if (c >= 0x10000 && c <= 0x1FFFFF && (i = 3) &&
					(tmp[3] = (((0x1C0000 & c) << 6) | 0xF0808080) >> 24))
				tmp[2] = (((0x3F000 & c) << 4) | 0x808080) >> 16;
		}
		tmp[4] = i + 1;
		while (i >= 0)
			write(1, &tmp[i--], 1);
	}
	return (tmp[4]);
}
