/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 20:21:22 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/10 10:02:55 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_clear_tab(char **tab)
{
	int		i;

	i = -1;
	while (tab[++i])
		ft_strdel(&tab[i]);
	ft_strdel((char **)&tab);
}

static int	ft_create_str(char *format, va_list list, t_colors colors)
{
	char	**array;
	char	*final_str;
	int		result;

	if (!(final_str = ft_strnew(1)))
		return (0);
	if (!(array = ft_str_parse(format)))
		return (0);
	if ((result = ft_convert_str(&final_str, array, list, colors)) < 0)
	{
		ft_clear_tab(array);
		ft_strdel(&final_str);
		return (-1);
	}
	write(1, final_str, result);
	ft_clear_tab(array);
	ft_strdel(&final_str);
	return (result);
}

int			ft_printf(const char *format, ...)
{
	int			result;
	va_list		list;
	t_colors	colors;

	result = 0;
	if (!*format)
		return (0);
	va_start(list, format);
	colors = colors_brackets();
	result = ft_create_str((char *)format, list, colors);
	va_end(list);
	return (result);
}
