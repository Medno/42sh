/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoindel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 13:45:09 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/12 14:13:01 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoindel(char *s1, char *s2)
{
	char	*tmp;

	if (s1 && s2)
	{
		if ((tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		{
			tmp = ft_strcat(tmp, s1);
			tmp = ft_strcat(tmp, s2);
			ft_strdel(&s1);
			return (tmp);
		}
	}
	else if (s1)
		return (s1);
	return (NULL);
}
