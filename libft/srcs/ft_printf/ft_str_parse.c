/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 14:30:44 by kyazdani          #+#    #+#             */
/*   Updated: 2017/12/08 16:36:03 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	array_length(char *str, char *argument)
{
	int		result;
	int		i;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '%' && (str[i + 1] == '%' || !(str[i + 1])))
			result++;
		if (str[i] == '%')
		{
			if (str[i + 1] == '%')
				i++;
			else
				i = i + ft_strcspn(&(str[i + 1]), argument) + 1;
			result++;
		}
		if (str[i])
			i++;
	}
	return (result);
}

static char	*fill_string(char *str)
{
	char	*new_string;

	if (*str == '%' && ft_strstrchr(&str[1], ARG_NAME))
	{
		if (!(new_string = ft_strndup(str, ft_strcspn(&(str[1]),
			ARG_NAME) + 2)))
			return (NULL);
	}
	else if (*str != '%')
	{
		if (!(new_string = ft_strndup(str, ft_strcspn(str, "%"))))
			return (NULL);
	}
	else
	{
		if (!(new_string = ft_strdup(str)))
			return (NULL);
	}
	return (new_string);
}

char		**ft_str_parse(char *str)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * (array_length(str,
		ARG_NAME) + 1))))
		return (NULL);
	while (str[i])
	{
		if (!(tab[j] = fill_string(&str[i])))
			return (NULL);
		if (str[i] == '%' && ft_strstrchr(&(str[i + 1]), ARG_NAME))
			i = i + ft_strcspn(&(str[i + 1]), ARG_NAME) + 2;
		else if (str[i] != '%')
			i = i + ft_strcspn(&(str[i]), "%");
		else
			i = i + ft_strlen(&(str[i]));
		j++;
	}
	tab[j] = 0;
	return (tab);
}
