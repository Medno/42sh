/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_esc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 18:13:31 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/12 17:46:32 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*esc_backslash(char *str, int *i)
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

char	*esc_simple_qu(char *str, int *i, int len)
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
		j = (str[j] == '\\') ? j + 1 : j;
		if (str[j])
		{
			buffer[k] = str[j];
			k++;
		}
		j++;
	}
	res = ft_strdup(buffer);
	*i = j;
	return (res);
}

char	*esc_double_qu(t_init *init, char *str, int *i, int len)
{
	char	*res;
	char	buffer[len + 1];
	int		j;
	int		k;

	(void)init;
	j = *i + 1;
	k = 0;
	ft_bzero(buffer, len);
	while (str[j] && str[j] != '\"')
	{
		j = (str[j] == '\\') ? j + 1 : j;
		if (str[j])
		{
			buffer[k] = str[j];
			k++;
		}
		j++;
	}
	res = ft_strdup(buffer);
	*i = j;
	return (res);
}
