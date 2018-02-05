/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 10:41:24 by kyazdani          #+#    #+#             */
/*   Updated: 2017/12/11 13:24:43 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*des;
	const char	*s;

	i = 0;
	des = dst;
	s = src;
	while (i < n)
	{
		des[i] = s[i];
		i++;
	}
	return (dst);
}
