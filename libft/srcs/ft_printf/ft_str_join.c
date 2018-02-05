/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:27:53 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/10 10:06:47 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_str_join(char *s1, char *s2, int size1, int size2)
{
	int		i;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	if ((str = (char *)malloc(sizeof(char) * (size1 + size2 + 1))) == NULL)
		return (NULL);
	while (i < size1)
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < size2)
	{
		str[size1] = s2[i];
		size1++;
		i++;
	}
	str[size1] = '\0';
	return (str);
}
