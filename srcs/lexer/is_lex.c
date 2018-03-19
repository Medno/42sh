/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_lex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 14:27:50 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/19 17:46:46 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		isredir(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int		is_op(char c, char buf[])
{
	if (c == '<' || c == '>' || c == '&' || c == '(' || c == ')'
			|| c == ';' || c == '|')
		return (1);
	if (buf[0] && buf[1] && buf[0] == '<' && buf[1] == '<' && c == '-')
		return (1);
	return (0);
}

int		is_number(char buf[])
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (!ft_isdigit(buf[i]))
			return (0);
		i++;
	}
	if (buf[0])
		return (1);
	return (0);
}
