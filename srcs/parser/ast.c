/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:21:18 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/16 12:22:29 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*command(t_lex *first)
{
	t_ast	*root;
	t_lex	*tmp;
	int		loop;

	tmp = first;
	root = init_ast();
	root->cmd = init_cmd();
	while (tmp)
	{
		loop = 1;
		root->value = CMD;
		if (is_redir(tmp) || tmp->token == IO_NUMBER)
			put_redir(root->cmd, tmp, &loop);
		else
			root->cmd = put_in_cmd(root->cmd, tmp);
		while (loop)
		{
			tmp = tmp->next;
			loop--;
		}
	}
	return (root);
}

t_ast	*pipeline(t_lex *first)
{
	t_ast	*root;
	t_lex	*sep;

	if ((sep = get_lex(first, OP, "|")))
	{
		root = init_ast();
		root->value = PIPE;
		if (sep->prev)
			sep->prev->next = NULL;
		root->left = command(first);
		if (sep->next && sep->next->token != EOI)
			root->right = pipeline(sep->next);
		del_lex(&sep);
		if (root->left)
			root->left->parent = root;
		if (root->right)
			root->right->parent = root;
	}
	else if (first->token != EOI)
		root = command(first);
	else
		root = NULL;
	return (root);
}

t_ast	*and_or(t_lex *first)
{
	t_ast	*root;
	t_lex	*sep;

	if ((sep = get_doublelex(first, AND_IF, OR_IF, NULL)))
	{
		root = init_ast();
		root->value = sep->token;
		if (sep->prev)
			sep->prev->next = NULL;
		root->left = and_or(first);
		if (sep->next && sep->next->token != EOI)
			root->right = and_or(sep->next);
		del_lex(&sep);
		if (root->left)
			root->left->parent = root;
		if (root->right)
			root->right->parent = root;
	}
	else
		root = pipeline(first);
	return (root);
}

t_ast	*build_ast(t_lex *first)
{
	t_ast	*root;
	t_lex	*sep;

	if ((sep = get_lex(first, NONE, "&")) ||
			(sep = get_lex(first, NONE, ";")))
	{
		if (sep->prev)
			sep->prev->next = NULL;
		root = init_ast();
		root->value = SEMI;
		root->left = and_or(first);
		if (sep->next && sep->next->token != EOI)
			root->right = build_ast(sep->next);
		del_lex(&sep);
		root->left->parent = root;
		if (root->right)
			root->right->parent = root;
	}
	else
		root = and_or(first);
	return (root);
}
