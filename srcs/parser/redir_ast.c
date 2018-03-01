/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 14:38:35 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/01 16:52:39 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_ast	*io_file(t_lex *first)
{
	t_ast	*root;

	if (first->next && first->next->token != WORD)
		return (0);
	if (first && first->next && first->next->token != EOI &&
			is_redir(first))
	{
		root = init_ast();
		root->value = ft_strdup("io");
		root->left = init_ast();
		root->left->value = ft_strdup(first->value);
		root->right = init_ast();
		root->right->value = ft_strdup(first->next->value);
		root->left->parent = root;
		root->right->parent = root;
		return (root);
	}
	return (NULL);
}

t_ast	*io_redirect(t_lex *first)
{
	t_ast	*root;

	root = NULL;
	if (first->token == IO_NUMBER && first->next->token != EOI)
	{
		root = init_ast();
		root->value = ft_strdup(first->value);
		root->left = io_redirect(first->next);
		if (root->left)
			root->left->parent = root;
		return (root);
	}
	root = io_file(first);
	return (root);
}
