/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:21:18 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/08 14:54:38 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*command_suf(t_lex *first)
{
	t_ast	*root;

	root = init_ast();
	if (first->token == WORD)
		root->value = ft_strdup(first->value);
	else if ((root->right = io_redirect(first)))
	{
		if (first->token == IO_NUMBER)
			first = first->next;
		first = first->next;
		root->right->parent = root;
		root->value = ft_strdup("io_redirect");
	}
	if (first && first->next && first->next->token != EOI)
	{
		root->left = command_suf(first->next);
		root->left->parent = root;
	}
	return (root);
}

t_ast	*command(t_lex *first)
{
	t_ast	*root;

	if (first->token == WORD)
	{
		root = init_ast();
		root->value = ft_strdup(first->value);
	}
	if (first->next && first->next->token != EOI)
	{
		if (first->token != WORD)
			root = command_suf(first);
		else
		{
			root->left = command_suf(first->next);
			root->left->parent = root;
		}
	}
	return (root);
}
/*
t_cmd	*put_redir(t_cmd *cmd, t_lex *tmp)
{
	cmd->redir = init_redir();
	cmd->redir = put_fd_in();
	if (is_number(tmp->value))
		tmp = tmp->next;
	cmd->redir->token = ft_strdup(tmp);
	tmp = tmp->next;
}

t_cmd	*put_in_cmd(t_cmd *cmd, t_lex *tmp)
{
}

t_ast	*command(t_lex *first)
{
	t_ast	*root;
	t_lex	*tmp;

	tmp = first;
	root = init_ast();
	root->cmd = init_cmd();
	while (tmp)
	{
		if (is_redir(tmp))
			root->cmd = put_redir(root->cmd, tmp);
		else
			root->cmd = put_in_cmd(root->cmd, tmp);
	}
	del_lex(first);
	return (root);
}
*/
t_ast	*pipeline(t_lex *first)
{
	t_ast	*root;
	t_lex	*sep;

	if ((sep = get_lex(first, OP, "|")))
	{
		root = init_ast();
		root->value = ft_strdup(sep->value);
		if (sep->prev)
			sep->prev->next = NULL;
		root->left = command(first);
		if (sep->next && sep->next->token != EOI)
			root->right = pipeline(sep->next);
		del_lex(sep);
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

	if ((sep = get_lex(first, AND_IF, NULL)) ||
			(sep = get_lex(first, OR_IF, NULL)))
	{
		root = init_ast();
		root->value = ft_strdup(sep->value);
		if (sep->prev)
			sep->prev->next = NULL;
		root->left = and_or(first);
		if (sep->next && sep->next->token != EOI)
			root->right = and_or(sep->next);
		del_lex(sep);
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
		root->value = ft_strdup(sep->value);
		root->left = and_or(first);
		if (sep->next && sep->next->token != EOI)
			root->right = build_ast(sep->next);
		del_lex(sep);
		root->left->parent = root;
		if (root->right)
			root->right->parent = root;
	}
	else
		root = and_or(first);
	return (root);
}
