/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 14:39:27 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/09 16:53:32 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*init_ast(void)
{
	t_ast	*tmp;

	if (!(tmp = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	tmp->value = NULL;
	tmp->cmd = NULL;
	tmp->parent = NULL;
	tmp->left = NULL;
	tmp->right = NULL;
	return (tmp);
}

void	clean_ast(t_ast **root)
{
	if (!*root)
		return ;
	if (*root && !(*root)->left && !(*root)->right)
	{
		ft_strdel(&((*root)->value));
		clean_cmd(&(*root)->cmd);
		free(*root);
		(*root) = NULL;
		return ;
	}
	if ((*root) && (*root)->left)
		clean_ast(&(*root)->left);
	if ((*root) && (*root)->right)
		clean_ast(&(*root)->right);
	clean_ast(root);
}
