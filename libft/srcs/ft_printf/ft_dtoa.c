/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 02:46:03 by kyazdani          #+#    #+#             */
/*   Updated: 2017/12/13 11:17:52 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*strround(char *str)
{
	int		len;

	len = ft_strlen(str) - 1;
	if (ft_strchr(str, '.'))
	{
		while ((str[len] >= '5' && len) || str[len] == '.')
		{
			if (str[len] == '.')
				len--;
			if (str[len] == '9')
				str[len] = '0';
			else
			{
				str[len]++;
				break ;
			}
			len--;
		}
	}
	return (str);
}

char			*ft_dtoa(double n, int prec, int apo)
{
	char	*str;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	if (!(tmp2 = ft_strnew(prec + 1)))
		return (NULL);
	if (prec > 0)
		tmp2[0] = '.';
	if (!(tmp = ft_ltoa((long long)n, apo)))
		return (NULL);
	if (n < 0)
		n = -n;
	if (ft_strlen(tmp) > 2)
		n = n - (unsigned long long)n;
	while (++i <= prec && (n *= 10.0))
		tmp2[i] = (unsigned long long)n % 10 + '0';
	if (!(str = ft_strjoin(tmp, tmp2)))
		return (NULL);
	str = strround(str);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	return (str);
}
