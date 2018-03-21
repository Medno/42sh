/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_glob.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 15:47:52 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/21 17:32:03 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob.h"

static void	check_quote_sl(char s, uint8_t *c, uint8_t *sl)
{
	if ((s == '\'' && !*c) || (s == '\'' && *c == 1))
		*c ^= 1;
	else if ((s == '\"' && !*c) || (s == '\"' && *c == 2))
		*c ^= 2;
	else if (s == '\\')
		*sl = 1;
}

static int	check_bracks(char *buf, char c)
{
	if (c == '[')
	{
		while (*buf)
		{
			if (ft_isalnum(*buf) || *buf == '!' || *buf == '-')
				buf++;
			else
				return (0);
		}
		return (2);
	}
	else if (c == '{')
	{
		if (!ft_strchr(buf, ','))
			return (0);
		while (*buf)
		{
			if (ft_isprint(*buf))
				buf++;
			else
				return (0);
		}
		return (3);
	}
	return (0);
}

static int	check_brack_expr(char **str)
{
	char	c;
	char	buf[ft_strlen(*str) + 1];
	int		i;

	c = **str;
	i = -1;
	ft_bzero(&buf[0], ft_strlen(*str) + 1);
	(*str)++;
	while (**str)
	{
		if (c == '{')
			if (**str == '}')
				break ;
		if (c == '[')
			if (**str == ']')
				break ;
		buf[++i] = **str;
		(*str)++;
	}
	if (buf[0])
		return (check_bracks(&buf[0], c));
	return (0);
}

int			check_glob(char *str)
{
	uint8_t	quote;
	uint8_t	slash;
	int		ret;

	quote = 0;
	slash = 0;
	while (*str)
	{
		check_quote_sl(*str, &quote, &slash);
		if ((*str == '*' || *str == '?') && !quote && !slash)
			return (1);
		else if ((*str == '{' || *str == '[') && !quote && !slash)
		{
			if ((ret = check_brack_expr(&str)))
				return (ret);
		}
		if (slash)
		{
			if (*(str + 1))
				str++;
			slash = 0;
		}
		str++;
	}
	return (0);
}
