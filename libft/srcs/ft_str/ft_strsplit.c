/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 11:05:42 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/08 09:09:52 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		count_w(const char *str, char c)
{
	int		words;
	int		i;

	words = 0;
	i = -1;
	while (str && str[++i])
	{
		if (str[i] != c && i != 0 && str[i - 1] == c)
			words++;
	}
	return (words);
		str++;
}

static	size_t	count_l(const char *str, char c)
{
	size_t	letters;

	letters = 0;
	while (*str != c && *str)
	{
		letters++;
		str++;
	}
	return (letters);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;

	if (!s)
		return (NULL);
	while (*s && *s == c)
		s++;
	if (!(i = count_w(s, c)))
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = -1;
	while (*s)
	{
		tab[++i] = ft_strndup(s, count_l(s, c));
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	tab[i] = NULL;
	return (tab);
}
