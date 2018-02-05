/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 09:17:08 by kyazdani          #+#    #+#             */
/*   Updated: 2017/11/09 12:14:21 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		count_char(int n)
{
	int				count;
	unsigned int	nb;

	count = 0;
	if (n < 0)
	{
		nb = -n;
		count = 1;
	}
	else
		nb = n;
	while (nb >= 10)
	{
		nb = nb / 10;
		count++;
	}
	count++;
	return (count);
}

char			*ft_itoa(int n)
{
	char			*str;
	int				i;
	int				len;
	int				end;
	unsigned int	nb;

	i = 0;
	len = count_char(n);
	end = len - 1;
	nb = n;
	if ((str = (char *)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	if (n < 0)
	{
		str[i++] = '-';
		nb = -n;
	}
	while (i < len)
	{
		str[end--] = nb % 10 + '0';
		nb = nb / 10;
		i++;
	}
	str[i] = '\0';
	return (str);
}
