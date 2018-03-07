/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_esc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 18:13:31 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/07 18:59:26 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*esc_backslash(char *res, char *str, int *i)
{
	char	read[2];
	int		j;

	j = *i + 1;
	read[0] = str[j];
	read[1] = '\0';
	if (read[0] != '\n')
		res = ft_strjoindel(res, read);
	*i = j;
	return (res);
}

char	*esc_simple_qu(char *res, char *str, int *i, int len)
{
	char	buffer[len + 1];
	int		j;

	j = *i + 1;
	ft_bzero(buffer, len);
	while (str[j] && str[j] != '\'')
	{
		buffer[j - *i - 1] = str[j];
		j++;
	}
	res = ft_strjoindel(res, buffer);
	*i = j;
	return (res);
}

char	*esc_double_qu(char *res, char *str, int *i, int len)
{
	char	buffer[len + 1];
	int		j;

	j = *i + 1;
	ft_bzero(buffer, len);
	while (str[j] && str[j] != '\"')
	{
		buffer[j - *i - 1] = str[j];
		j++;
	}
	res = ft_strjoindel(res, buffer);
	*i = j;
	return (res);
}
