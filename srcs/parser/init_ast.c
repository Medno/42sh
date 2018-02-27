/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 14:39:27 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/27 15:57:09 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_ast	*init_ast(void)
{
	t_ast	*tmp;

	if (!(tmp = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
//	tmp->lex = NULL;
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
