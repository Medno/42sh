/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 13:27:35 by pchadeni          #+#    #+#             */
/*   Updated: 2018/04/17 10:21:49 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parser(t_init *init)
{
	t_lex	*tmp;
	t_ast	*ast;
	int		repeat;

	if (check_first(init->lex))
		return ((g_status = 258));
	tmp = init->lex;
	while (tmp->token != EOI)
	{
		if (err_pars(tmp))
			return ((g_status = 258));
		repeat = repeat_line(init, tmp);
		if (repeat == 1)
			return (-1);
		else if (repeat == -1)
			return (1);
		tmp = tmp->next;
	}
	tmp = init->lex;
	ast = build_ast(tmp);
	init->ast = ast;
	return (0);
}
