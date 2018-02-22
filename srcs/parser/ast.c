/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:21:18 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/22 17:26:45 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_lex   get_lex(t_lex *first, t_token token, char *value)
{
	t_lex   *tmp;

	t4mp = first;
	while (tmp)
	{
		if (value && ft_strequ(value, tmp->value))
			return (tmp);
		if (!value && token != NONE)
			if (token == tmp->token)
				return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

t_ast   and_if(t_lex *first)
{

}

t_ast   *build_ast(t_lex *first)
{
	t_ast   *root;
	t_lex   *sep;

	root = init_ast(root);
	if (/*(sep = get_lex(first, NONE, "&")) || */(sep = get_lex(first, NONE, ";")))
	{
		root->value = sep->value;
		root->left = and_if(first);
		root->right = build_ast(set->next);
	}
	else
		root->left = and_if(first);
	return (root);
}
