/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:32:13 by pchadeni          #+#    #+#             */
/*   Updated: 2018/04/11 12:33:40 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	concat_char(char *str, int i, char buf[])
{
	if ((is_closing(str[i]) && g_quote != '\\') ||
			(g_quote == '\\' && str[i] != '\n'))
		g_quote = 0;
	if (g_quote == '\\' && str[i + 1])
		g_quote = 0;
	put_in_buffer(buf, str[i]);
}

t_lex	*new_word(t_lex *new, char *str, int i, char buf[])
{
	int		len;

	len = ft_strlen(buf);
	ft_bzero(buf, len);
	put_in_buffer(buf, str[i]);
	new->token = WORD;
	return (new);
}

t_lex	*end_of_new(t_lex *new, char buf[])
{
	if (new->token != NONE)
		new = put_in_new(new, buf);
	new->token = EOI;
	return (new);
}
