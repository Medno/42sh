/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoindel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 11:26:34 by hlely             #+#    #+#             */
/*   Updated: 2018/03/09 14:21:24 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoindel(char *s1, char *s2, size_t n)
{
	char	*tmp;

	if (s1 && s2)
	{
		if (!n)
			return (ft_strjoindel(s1, s2));
		if ((tmp = ft_strnew(n)))
		{
			tmp = ft_strcat(tmp, s1);
			tmp = ft_strncat(tmp, s2, n - ft_strlen(s1));
			ft_strdel(&s1);
			return (tmp);
		}
	}
	return (NULL);
}
