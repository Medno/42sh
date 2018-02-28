/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_infinite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 11:58:41 by hfouques          #+#    #+#             */
/*   Updated: 2018/02/04 11:58:46 by hfouques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_total_length(int i, va_list ap, char *format)
{
	size_t ret;

	ret = ft_strlen(format);
	while (--i > 0)
	{
		ret += ft_strlen(va_arg(ap, char *));
	}
	return (ret);
}

static char		*ft_fill_ret(int i, va_list ap, char *format, size_t length)
{
	char *ret;

	ret = ft_strnew(length);
	ret = ft_strcpy(ret, format);
	while (--i > 0)
		ret = ft_strcat(ret, va_arg(ap, char *));
	return (ret);
}

char			*ft_strjoin_infinite(int i, char *format, ...)
{
	va_list ap;
	char	*ret;
	size_t	length;

	if (!format)
		return (NULL);
	va_start(ap, format);
	length = get_total_length(i, ap, format);
	va_start(ap, format);
	ret = ft_fill_ret(i, ap, format, length);
	va_end(ap);
	return (ret);
}
