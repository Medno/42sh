/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 06:53:49 by kyazdani          #+#    #+#             */
/*   Updated: 2017/12/13 11:17:39 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*strround(char *str)
{
	int		len;

	len = ft_strlen(str) - 1;
	if (ft_strchr(str, '.'))
	{
		while ((str[len] == '9' && len) || str[len] == '.')
		{
			if (str[len] == '.')
				len--;
			if (str[len] == '9')
			{
				str[len] = '0';
				str[len - 1]++;
			}
			else
				break ;
			len--;
		}
	}
	return (str);
}

char		*ft_ldtoa(long double n, int prec, int apo)
{
	char	*str;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	if (prec > 0)
	{
		if (!(tmp = ft_strnew(prec + 1)))
			return (NULL);
		tmp[0] = '.';
	}
	tmp2 = ft_ltoa((unsigned long long)n, apo);
	n = n < 0 ? -1 * n : n;
	n = n - (unsigned long long)n;
	while (++i <= prec && (n *= 10) >= 0)
	{
		tmp[i] = (unsigned long long)n % 10 + '0';
		n = n - (char)n;
	}
	str = ft_strjoin(tmp2, tmp);
	str = strround(str);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	return (str);
}
