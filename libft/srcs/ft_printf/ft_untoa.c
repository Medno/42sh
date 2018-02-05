/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_untoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 09:17:08 by kyazdani          #+#    #+#             */
/*   Updated: 2017/12/13 11:17:09 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		count_char(unsigned long long n, int apo)
{
	int				count;
	int				i;
	int				tmp;

	count = 1;
	i = -1;
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	tmp = count;
	while (++i <= tmp && apo == 1)
	{
		if (i % 3 == 0 && i + 1 <= tmp && i != 0)
			count++;
	}
	return (count);
}

char			*ft_untoa(unsigned long long n, int apo)
{
	char			*str;
	int				i;
	int				len;
	int				end;

	i = 0;
	len = count_char(n, apo);
	end = len - 1;
	if ((str = (char *)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	while (i < len)
	{
		if (i % 3 == 0 && apo == 1 && i != 0)
		{
			str[end] = ',';
			end--;
		}
		str[end--] = n % 10 + '0';
		n = n / 10;
		i++;
	}
	str[i] = '\0';
	return (str);
}
