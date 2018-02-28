/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:21:18 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/28 10:22:39 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	print_ast(t_ast *root, char *pos)
{
	if (root->value)
	{
		if (pos)
			ft_putendl(pos);
		if (!root->parent)
			ft_putendl("Racine");
		else
		{
			ft_putstr("Fils de : ");
			ft_putendl(root->parent->value);
		}
		ft_putendl(root->value);
		if (root->left)
			print_ast(root->left, "Fils Gauche");
		if (root->right)
			print_ast(root->right, "Fils Droit");
	}
}

t_lex   *get_lex(t_lex *first, t_token token, char *value)
{
	t_lex   *tmp;

	tmp = first;
	while (tmp && tmp->token != EOI)
	{
		if (value && ft_strequ(value, tmp->value))
			return (tmp);
		if (!value && token != NONE)
			if (token == tmp->token)
				return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_ast	*io_file(t_lex **first)
{
	t_ast	*root;

	if (*first && (*first)->next->token != EOI)
	{
		if ((*first)->next->token != WORD)
			return (0);
		if (ft_strequ((*first)->value, ">") || ft_strequ((*first)->value, "<") ||
				(*first)->token == LESSAND || (*first)->token == GREATAND ||
				(*first)->token == DGREAT || (*first)->token == LESSGREAT ||
				(*first)->token == CLOBBER || (*first)->token == DLESS
				|| (*first)->token == DLESSDASH)
		{
			root = init_ast();
			root->value = ft_strdup("io");
			root->left = init_ast();
			root->left->value = ft_strdup((*first)->value);
			root->right = init_ast();
			root->right->value = ft_strdup((*first)->next->value);
			root->left->parent = root;
			root->right->parent = root;
			(*first) = (*first)->next;
			if (*first)
				(*first) = (*first)->next;
			return (root);
		}
	}
	return (NULL);
}

t_ast	*io_redirect(t_lex **first)
{
	t_ast	*root;

	root = NULL;
	if ((*first)->token == IO_NUMBER && (*first)->next->token != EOI)
	{
		root = init_ast();
		root->value = ft_strdup((*first)->value);
		root->left = io_redirect(&(*first)->next);
		if (root->left)
			root->left->parent = root;
		return (root);
	}
	root = io_file(first);
	return (root);
}

t_ast	*command_suf(t_lex *first)
{
	t_ast	*root;
	t_lex	*tmp;

	root = init_ast();
	tmp = first;
	if (first->token == WORD)
		root->value = ft_strdup(first->value);
	else if ((root->left = io_redirect(&tmp)))
	{
		root->left->parent = root;
		root->value = ft_strdup("io_redirect");
		first = tmp;
	}
	else
		;//error
	if (first && first->next && first->next->token != EOI)
	{
		root->right = command_suf(first->next);
		root->right->parent = root;
	}
	return (root);
}

t_ast	*command(t_lex *first)
{
	t_ast	*root;

	root = init_ast();
	root->value = ft_strdup(first->value);
	if (first->next && first->next->token != EOI)
	{
		root->left = command_suf(first->next);
		root->left->parent = root;
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
		root->value = ft_strdup(sep->value);
		if (sep->prev)
			sep->prev->next = NULL;
		if (sep->next && sep->next->token != EOI)
			root->left = command(sep->next);
		del_lex(sep);
		root->right = pipeline(first);
		root->left->parent = root;
		root->right->parent = root;
	}
	else if (first->token != EOI)
		root = command(first);
	else
		root = NULL;
	return (root);
}

t_ast   *and_or(t_lex *first)
{
	t_ast	*root;
	t_lex	*sep;

	if ((sep = get_lex(first, AND_IF, NULL)) || (sep = get_lex(first, OR_IF, NULL)))
	{
		root = init_ast();
		root->value = ft_strdup(sep->value);
		if (sep->prev)
			sep->prev->next = NULL;
		if (sep->next && sep->next->token != EOI)
		{
			root->left = pipeline(sep->next);
			if (root->left)
			root->left->parent = root;
		}
		del_lex(sep);
		root->right = and_or(first);
		root->right->parent = root;
	}
	else
		root = pipeline(first);
	return (root);
}

t_ast   *build_ast(t_lex *first)
{
	t_ast   *root;
	t_lex   *sep;

	//TODO : Free all the tree and t_lex
	if ((sep = get_lex(first, NONE, "&")) || (sep = get_lex(first, NONE, ";")))
	{
		root = init_ast();
		root->value = ft_strdup(sep->value);
		if (sep->prev)
			sep->prev->next = NULL;
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
