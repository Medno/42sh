/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:59:29 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/10 09:41:38 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <inttypes.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n >= sizeof(uintmax_t))
	{
		if (*(uintmax_t *)s1 != *(uintmax_t *)s2)
		{
			while (*(unsigned char *)s1 == *(unsigned char *)s2 && (s1++))
				s2++;
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		}
		n -= sizeof(uintmax_t);
		s1 += sizeof(uintmax_t);
		s2 += sizeof(uintmax_t);
	}
	while (n--)
	{
		if (*(unsigned char *)s1 == *(unsigned char *)s2 && (s1++) && (s2++))
			;
		else
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
	}
	return (0);
}
