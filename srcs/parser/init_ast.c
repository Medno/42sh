/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 14:39:27 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/01 13:56:51 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_ast	*init_ast(void)
{
	t_ast	*tmp;

	if (!(tmp = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	tmp->value = NULL;
	tmp->parent = NULL;
	tmp->left = NULL;
	tmp->right = NULL;
	return (tmp);
}

void	del_ast(t_ast **root)
{
	if (*root && !(*root)->left && !(*root)->right)
	{
		ft_strdel(&((*root)->value));
		free(*root);
		(*root) = NULL;
		return ;
	}
	if ((*root) && (*root)->left)
		del_ast(&(*root)->left);
	if ((*root) && (*root)->right)
		del_ast(&(*root)->right);
	del_ast(root);
}

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
