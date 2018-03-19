/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brack_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 12:09:07 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/19 17:45:25 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		is_brack(char c)
{
	if (c == '{' || c == '(')
		return (1);
	return (0);
}

int		is_esc(char c)
{
	if (c == '\\' || c == '\'' || c == '\"' || c == '`' || is_brack(c))
		return (1);
	return (0);
}

int		is_closing(char c)
{
	if (g_quote == '{' && c == '}')
		return (1);
	if (g_quote == '(' && c == ')')
		return (1);
	if (g_quote == '\'' && c == '\'')
		return (1);
	if (g_quote == '\"' && c == '\"')
		return (1);
	if (g_quote == '`' && c == '`')
		return (1);
	return (0);
}
