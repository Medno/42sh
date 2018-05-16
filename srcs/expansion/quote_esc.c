/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_esc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 18:13:31 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/16 15:43:45 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char		*esc_backslash(char *str, int *i)
{
	char	*res;
	char	read[2];
	int		j;

	res = NULL;
	j = *i + 1;
	read[0] = str[j];
	read[1] = '\0';
	if (read[0] != '\n')
		res = ft_strdup(read);
	*i = j;
	return (res);
}

char		*esc_simple_qu(char *str, int *i, int len)
{
	char	*res;
	char	buffer[len + 1];
	int		j;
	int		k;

	j = *i + 1;
	k = 0;
	ft_bzero(buffer, len);
	while (str[j] && str[j] != '\'')
	{
		buffer[k] = str[j];
		k++;
		j++;
	}
	if (!str[j])
		return (NULL);
	res = ft_strdup(buffer);
	*i = j;
	return (res);
}

static int	incr_backslash(int j, char c)
{
	if (c == '\\' || c == '\"' || c == '$' || c == '`'
		|| c == '\n')
		return (j + 1);
	return (j);
}

char		*esc_double_qu(char *str, int *i, int len)
{
	char	*res;
	char	buffer[len + 1];
	int		j;
	int		k;

	j = *i + 1;
	k = 0;
	ft_bzero(buffer, len);
	while (str[j] && str[j] != '\"')
	{
		if (str[j] == '\\' && str[j + 1])
			j = incr_backslash(j, str[j + 1]);
		if (str[j] && !(str[j] == '\n' && str[j - 1] == '\\'))
		{
			buffer[k] = str[j];
			k++;
		}
		j++;
	}
	if (!str[j])
		return (NULL);
	res = ft_strdup(buffer);
	*i = j;
	return (res);
}
