/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:32:13 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/12 14:57:01 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	concat_char(char *str, int i, char buf[])
{
	char	read[2];

	read[0] = str[i];
	read[1] = '\0';
	if ((str[i] == g_quote && g_quote != '\\') ||
			(g_quote == '\\' && str[i] != '\n'))
		g_quote = 0;
	if (g_quote == '\\' && str[i + 1])
		g_quote = 0;
	ft_strcat(buf, read);
}

t_lex	*new_word(t_lex *new, char *str, int i, char buf[])
{
	char	read[2];
	int		len;

	len = ft_strlen(buf);
	read[0] = str[i];
	read[1] = '\0';
	ft_bzero(buf, len);
	ft_strcat(buf, read);
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
