/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_brackets.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:40:30 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/10 10:07:39 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	countab(char *str, t_colors colors)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '{')
		{
			if (is_valid(&str[i], colors))
			{
				count++;
				while (str[i] != '}')
					i++;
			}
		}
		else if ((str[i + 1] == '{' && is_valid(&str[i + 1], colors))
				|| !str[i + 1])
			count++;
	}
	return (count);
}

static char	*ft_putinstr_brackets(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	while (str[i] != '}' && str[i])
	{
		i++;
		count++;
	}
	str = ft_strndup(str, count);
	return (str);
}

static char	*ft_putinstr_str(char *str, t_colors colors)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i + 1] && (str[i] != '{' || (str[i] == '{'
				&& !is_valid(&str[i], colors))))
	{
		i++;
		count++;
	}
	if (!str[i + 1])
		count++;
	str = ft_strndup(str, count);
	return (str);
}

static int	place_index(char *str, int i, t_colors colors)
{
	if (str[i] == '{' && is_valid(&str[i], colors))
	{
		while (str[i] != '}')
			i++;
		return (i + 1);
	}
	else
	{
		while (str[i] && (str[i] != '{' || (str[i] == '{'
				&& !is_valid(&str[i], colors))))
			i++;
	}
	return (i);
}

char		**ft_parse_brackets(char *str, t_colors colors)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!(tab = (char **)malloc(sizeof(char *) * (countab(str, colors) + 1))))
		return (NULL);
	while (str[i])
	{
		if (str[i] == '{' && is_valid(&str[i], colors))
			tab[++j] = ft_putinstr_brackets(&str[i]);
		else
			tab[++j] = ft_putinstr_str(&str[i], colors);
		i = place_index(str, i, colors);
	}
	tab[++j] = 0;
	return (tab);
}
