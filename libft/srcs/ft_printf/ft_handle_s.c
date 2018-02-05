/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:10:09 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/10 10:06:27 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_prec_s(char *str, t_flags flags)
{
	if (flags.precision < ft_strlen(str) && flags.point)
		str[flags.precision] = '\0';
	return (str);
}

static char	*ft_convert_s_maj(wchar_t *chr, int result)
{
	int		i;
	char	*str;
	int		len;
	char	*tmp;
	char	*tmp2;

	i = -1;
	len = 0;
	str = ft_strnew(1);
	while (chr[++i] && i < result)
	{
		tmp = str;
		tmp2 = ft_convert_wct(chr[i]);
		str = ft_str_join(str, tmp2,
				len, handle_wchar_ret_nocurmax(chr[i]));
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
		len = len + handle_wchar_ret_nocurmax(chr[i]);
	}
	return (str);
}

static int	ft_s_min(t_flags flags, char *content, char **str)
{
	char	*tmp;

	tmp = *str;
	if (!content)
	{
		if (!(*str = ft_strdup("(null)")))
			return (0);
	}
	else
	{
		if (!(*str = ft_strdup(content)))
			return (0);
	}
	ft_strdel(&tmp);
	if (flags.point && flags.precision < ft_strlen(*str))
		*str = ft_prec_s(*str, flags);
	return (ft_strlen(*str));
}

static int	ft_s_maj(t_flags flags, char **str, wchar_t *content)
{
	int		result;
	char	*tmp;

	result = 0;
	if (!content && (tmp = *str))
	{
		*str = ft_strdup("(null)");
		ft_strdel(&tmp);
		*str = ft_prec_s(*str, flags);
		result = flags.precision < 6 && flags.point ? flags.precision : 6;
	}
	else if ((tmp = *str))
	{
		if ((result = ft_handle_return_s(content, flags)) == -1)
			return (result);
		*str = ft_convert_s_maj(content, result);
		ft_strdel(&tmp);
	}
	return (result);
}

int			ft_handle_s(t_flags flags, char **str, va_list list)
{
	int		result;
	void	*content;

	result = 0;
	if (flags.letter == 'S' || flags.l)
	{
		content = va_arg(list, wchar_t *);
		if ((result = ft_s_maj(flags, str, content)) < 0)
			return (-1);
	}
	else if (flags.letter == 's')
	{
		content = va_arg(list, char *);
		result = ft_s_min(flags, content, str);
	}
	if (flags.width > result)
	{
		*str = handle_width_cs(flags, *str, result);
		result = flags.width;
	}
	return (result);
}
