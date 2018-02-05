/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:46:36 by kyazdani          #+#    #+#             */
/*   Updated: 2017/11/09 12:11:16 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	const char	*s;
	char		*dest;

	s = src;
	dest = dst;
	i = 0;
	while (dest + i > s + i && i < len)
	{
		dest[len - i - 1] = s[len - i - 1];
		i++;
	}
	while (i < len)
	{
		dest[i] = s[i];
		i++;
	}
	return (dst);
}
