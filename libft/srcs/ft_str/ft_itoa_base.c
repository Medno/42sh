/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 09:17:08 by kyazdani          #+#    #+#             */
/*   Updated: 2017/11/27 12:45:28 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		count_char(unsigned long long n, unsigned int base_nb)
{
	int				count;

	count = 0;
	while (n >= base_nb)
	{
		n = n / base_nb;
		count++;
	}
	count++;
	return (count);
}

char			*ft_itoa_base(unsigned long long n, char *base,
				unsigned int base_nb)
{
	char			*str;
	int				i;
	int				len;
	int				end;

	i = 0;
	len = count_char(n, base_nb);
	end = len - 1;
	if ((str = (char *)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	while (i < len)
	{
		str[end] = base[n % base_nb];
		n = n / base_nb;
		i++;
		end--;
	}
	str[i] = '\0';
	return (str);
}
