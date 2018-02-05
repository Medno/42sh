/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:21:12 by kyazdani          #+#    #+#             */
/*   Updated: 2017/12/11 13:04:05 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n)
	{
		*(char *)dst = *(char *)src;
		if (*(unsigned char *)src == (unsigned char)c)
			return (dst + 1);
		n--;
		dst++;
		src++;
	}
	return (NULL);
}
