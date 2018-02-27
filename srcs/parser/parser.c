/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 13:27:35 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/27 14:35:53 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int	parser(t_lex *first)
{
	t_lex	*tmp;
	t_ast	*ast;
	int		build;

	build = 1;
//		print_lex(first);
	if (first->token != WORD)
	{
		if (first->token != EOI)
			ft_putendl("syntax error");
		build = 0;
	}
	tmp = first;
	while (tmp->token != EOI && build)
	{
		if (tmp->token != WORD && tmp->token != IO_NUMBER
				&& !ft_strequ(";", tmp->value) && tmp->next && tmp->next->token == EOI)
		{
			ft_putendl("syntax error");
			build = 0;
		}
		tmp = tmp->next;
	}
	if (build)
	{
		tmp = first;
		ast = build_ast(tmp);
		print_ast(ast, NULL);
		del_ast(&ast);
	}
	del_lex(first);
	return (0);
}
