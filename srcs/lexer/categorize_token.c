/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorize_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:26:49 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/08 13:59:13 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_lex	*categorize_op(t_lex *new)
{
	if (ft_strequ("&&", new->value))
		new->token = AND_IF;
	else if (ft_strequ("||", new->value))
		new->token = OR_IF;
	else if (ft_strequ(";;", new->value))
		new->token = DSEMI;
	else if (ft_strequ("<<", new->value))
		new->token = DLESS;
	else if (ft_strequ(">>", new->value))
		new->token = DGREAT;
	else if (ft_strequ("<&", new->value))
		new->token = LESSAND;
	else if (ft_strequ(">&", new->value))
		new->token = GREATAND;
	else if (ft_strequ("&<", new->value))
		new->token = ANDLESS;
	else if (ft_strequ("&>", new->value))
		new->token = ANDGREAT;
	else if (ft_strequ("<>", new->value))
		new->token = LESSGREAT;
	else if (ft_strequ("<<-", new->value))
		new->token = DLESSDASH;
	else if (ft_strequ(">|", new->value))
		new->token = CLOBBER;
	return (new);
}

static t_lex	*categorize_rsvword(t_lex *new)
{
	new->token = (ft_strequ("if", new->value)) ? new->token = IF : new->token;
	new->token = (ft_strequ("fi", new->value)) ? new->token = FI : new->token;
	new->token = (ft_strequ("do", new->value)) ? new->token = DO : new->token;
	if (ft_strequ("else", new->value))
		new->token = ELSE;
	else if (ft_strequ("elif", new->value))
		new->token = ELIF;
	else if (ft_strequ("done", new->value))
		new->token = DONE;
	else if (ft_strequ("for", new->value))
		new->token = FOR;
	else if (ft_strequ("case", new->value))
		new->token = CASE;
	else if (ft_strequ("esac", new->value))
		new->token = ESAC;
	else if (ft_strequ("in", new->value))
		new->token = IN;
	else if (ft_strequ("then", new->value))
		new->token = THEN;
	else if (ft_strequ("until", new->value))
		new->token = UNTIL;
	else if (ft_strequ("while", new->value))
		new->token = WHILE;
	return (new);
}

static t_lex	*categorize_token(t_lex *new)
{
	if (new->token == OP)
		new = categorize_op(new);
	else if (!new->value)
		new->token = EOI;
	else if (ft_strequ("\n", new->value))
		new->token = NEWLINE;
	if (new->token == WORD && g_quote)
		new->token = QUOTE;
	else if (new->token == QUOTE && !g_quote)
		new->token = WORD;
	if (new->token == WORD)
		new = categorize_rsvword(new);
	if (new->token == WORD && new->prev &&
			new->prev->token == DLESS)
		new->token = IO_HERE;
	return (new);
}

t_lex			*put_in_new(t_lex *new, char *buf)
{
	int	len;

	len = ft_strlen(buf);
	new->value = ft_strdup(buf);
	new = categorize_token(new);
	ft_bzero(buf, len);
	new->next = init_lexer();
	new->next->prev = new;
	new = new->next;
	return (new);
}
