/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:34:19 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/22 10:29:12 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t			i;
	unsigned int	start;
	size_t			end;

	if (!s)
		return (NULL);
	i = 0;
	start = 0;
	end = ft_strlen(s) - 1;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && s[i] != '\0')
		i++;
	start = (unsigned int)i;
	while ((s[end] == ' ' || s[end] == '\n' || s[end] == '\t') && s[i] != '\0')
	{
		end--;
		i++;
	}
	return (ft_strsub(s, start, end - start + 1));
}
