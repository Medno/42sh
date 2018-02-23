/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:21:18 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/23 16:40:18 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	print_ast(t_ast *root, char *pos)
{
	t_ast	*tmp;

	tmp = root;
	if (root->value)
	{
		ft_putendl(pos);
//	print_lex(root->value);
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
	while (tmp)
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

int		is_io_file(t_lex *first)
{
	if (first->next)
	{
		if (first->next->token != WORD)
			return (0);
		if (ft_strequ(first->value, ">") || ft_strequ(first->value, "<") ||
				first->token == LESSAND || first->token == GREATAND ||
				first->token == DGREAT || first->token == LESSGREAT ||
				first->token == CLOBBER)
			return (1);
	}
	return (0);
}

int		is_io_here(t_lex *first)
{
	if ()
}

int		is_io_redir(t_lex *first)
{
	if (first->next)
	{
		if (first->token == IO_NUMBER)
			if (is_io_file(first->next) || is_io_here(first->next))
				return (1);
	}
	else
		if (is_io_file || is_io_here)
			return (1);
	return (0);
}

t_ast	*io_redirect(t_lex *first)
{
	t_ast	*root;
	t_ast	*tmp;

	root = NULL;
	tmp = root;
	if (first->token == IO_NUMBER && first->next)
	{
		root->left = init_ast(root->left);
		root->left->value = ft_strdup(first->value);
		//free(first)
		first = first->next;
		root = root->right;
	}
	//TODO
	if ((root = io_file(first)) || root = io_here(first))
	return (root);
}

t_ast	*command_suf(t_lex *first)
{
	t_ast	*root;

	root = init_ast();
	if (first->token == WORD)
		root->value = first->value;
	else if (root->left = io_redirect(first))
		root->value = ft_strdup("io_redirect");
	else
		;//error
	if (first->next)
	{
		if ()
		root->right = command_suf(first->next);
	}
	return (root);
}

t_ast	*command(t_lex *first)
{
	t_ast	*root;

	root = init_ast();
	root->value = first->value;
	if (first->next)
		root->left = command_suf(first->next);
	return (root);
}

t_ast	*pipeline(t_lex *first)
{
	t_ast	*root;
	t_lex	*sep;

	root = init_ast();
	if ((sep = get_lex(first, OP, "|")))
	{
		root->value = sep->value;
		if (sep->prev)
			sep->prev->next = NULL;
		root->left = command(sep->next);
		root->right = pipeline(first);
	}
	else
		root = command(first);
	return (root);
}

t_ast   *and_or(t_lex *first)
{
	t_ast	*root;
	t_lex	*sep;

	root = init_ast();
	if ((sep = get_lex(first, AND_IF, NULL)) || (sep = get_lex(first, OR_IF, NULL)))
	{
		root->value = sep->value;
		if (sep->prev)
			sep->prev->next = NULL;
		root->left = pipeline(sep->next);
		root->right = and_or(first);
	}
	else
		root = pipeline(first);
	return (root);
}

t_ast   *build_ast(t_lex *first)
{
	t_ast   *root;
	t_lex   *sep;

	root = init_ast();
	if (/*(sep = get_lex(first, NONE, "&")) || */(sep = get_lex(first, NONE, ";")))
	{
		root->value = sep->value;
		if (sep->prev)
			sep->prev->next = NULL;
		root->left = and_or(first);
		root->right = build_ast(sep->next);
	}
	else
		root = and_or(first);
	print_ast(root, "Parent racine");
	return (root);
}
