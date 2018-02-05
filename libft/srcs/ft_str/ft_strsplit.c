/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 11:05:42 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/10 11:45:24 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		count_w(const char *str, char c)
{
	int		words;
	int		i;

	words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && (i == 0 || str[i - 1] == c))
			words++;
		i++;
	}
	return (words);
}

static	size_t	count_l(const char *str, char c, int i)
{
	size_t	letters;

	letters = 0;
	while (str[i] != c && str[i] != '\0')
	{
		letters++;
		i++;
	}
	return (letters);
}

static	char	**split_tab(char **tab, const char *s, char c)
{
	int		x;
	int		index;
	int		i;

	x = 0;
	i = 0;
	index = 0;
	while (s[i] != '\0' && i < ft_strlen(s))
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			tab[index] = ft_strnew(count_l(s, c, i));
			while (s[i] != c && s[i] != '\0')
			{
				tab[index][x] = s[i];
				i++;
				x++;
			}
			x = 0;
			index++;
		}
		i++;
	}
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		word_number;

	if (!s)
		return (NULL);
	word_number = count_w(s, c);
	if ((tab = (char **)malloc(sizeof(char *) * (word_number + 1))) == NULL)
		return (NULL);
	tab = split_tab(tab, s, c);
	tab[word_number] = 0;
	return (tab);
}
