/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 08:26:40 by kyazdani          #+#    #+#             */
/*   Updated: 2017/11/27 15:54:09 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *s, const char *charset)
{
	int		i;
	int		j;

	j = 0;
	while (s[j])
	{
		i = 0;
		while (charset[i])
		{
			if (charset[i] == s[j])
				return (j);
			i++;
			if (!charset[i])
				break ;
		}
		j++;
	}
	return (j);
}
