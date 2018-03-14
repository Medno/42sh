/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:21:18 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/14 14:23:46 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*command(t_init *init, t_lex *first)
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
		if (is_redir(tmp) || tmp->token == IO_NUMBER)
			put_redir(root->cmd, tmp, &loop);
		else
		{
			root->value = CMD;
			root->cmd = put_in_cmd(init, root->cmd, tmp);
		}
		while (loop)
		{
			tmp = tmp->next;
			loop--;
		}
	}
	return (root);
}

t_ast	*pipeline(t_init *init, t_lex *first)
{
	t_ast	*root;
	t_lex	*sep;

	if ((sep = get_lex(first, OP, "|")))
	{
		root = init_ast();
		root->value = PIPE;
		if (sep->prev)
			sep->prev->next = NULL;
		root->left = command(init, first);
		if (sep->next && sep->next->token != EOI)
			root->right = pipeline(init, sep->next);
		del_lex(sep);
		if (root->left)
			root->left->parent = root;
		if (root->right)
			root->right->parent = root;
	}
	else if (first->token != EOI)
		root = command(init, first);
	else
		root = NULL;
	return (root);
}

t_ast	*and_or(t_init *init, t_lex *first)
{
	t_ast	*root;
	t_lex	*sep;

	if ((sep = get_lex(first, AND_IF, NULL)) ||
			(sep = get_lex(first, OR_IF, NULL)))
	{
		root = init_ast();
		root->value = sep->token;
		if (sep->prev)
			sep->prev->next = NULL;
		root->left = and_or(init, first);
		if (sep->next && sep->next->token != EOI)
			root->right = and_or(init, sep->next);
		del_lex(sep);
		if (root->left)
			root->left->parent = root;
		if (root->right)
			root->right->parent = root;
	}
	else
		root = pipeline(init, first);
	return (root);
}

t_ast	*build_ast(t_init *init, t_lex *first)
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
		root->left = and_or(init, first);
		if (sep->next && sep->next->token != EOI)
			root->right = build_ast(init, sep->next);
		del_lex(sep);
		root->left->parent = root;
		if (root->right)
			root->right->parent = root;
	}
	else
		root = and_or(init, first);
	return (root);
}
