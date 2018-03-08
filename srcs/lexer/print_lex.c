/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 14:26:37 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/08 14:03:43 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	print_type_2(t_lex *tmp)
{
	if (tmp->token == DLESS)
		ft_putendl("DLESS");
	if (tmp->token == DGREAT)
		ft_putendl("DGREAT");
	if (tmp->token == LESSAND)
		ft_putendl("LESSAND");
	if (tmp->token == GREATAND)
		ft_putendl("GREATAND");
	if (tmp->token == ANDLESS)
		ft_putendl("ANDLESS");
	if (tmp->token == ANDGREAT)
		ft_putendl("ANDGREAT");
	if (tmp->token == LESSGREAT)
		ft_putendl("LESSGREAT");
	if (tmp->token == DLESSDASH)
		ft_putendl("DLESSDASH");
	if (tmp->token == CLOBBER)
		ft_putendl("CLOBBER");
}

static void	print_type(t_lex *tmp)
{
	ft_putstr("Type : ");
	if (tmp->token == NONE)
		ft_putendl("NONE");
	if (tmp->token == IO_HERE)
		ft_putendl("IO_HERE");
	if (tmp->token == WORD)
		ft_putendl("WORD");
	if (tmp->token == OP)
		ft_putendl("OP");
	if (tmp->token == IO_NUMBER)
		ft_putendl("IO_NUMBER");
	if (tmp->token == EOI)
		ft_putendl("EOI");
	if (tmp->token == AND_IF)
		ft_putendl("AND_IF");
	if (tmp->token == OR_IF)
		ft_putendl("OR_IF");
	if (tmp->token == DSEMI)
		ft_putendl("DSEMI");
	print_type_2(tmp);
}

void		print_lex(t_lex *first)
{
	t_lex	*tmp;
	int		i;

	tmp = first;
	i = 1;
	while (tmp)
	{
		ft_printf("Token n. : %d\n", i);
		print_type(tmp);
		ft_putendl(tmp->value);
		i++;
		tmp = tmp->next;
	}
}
