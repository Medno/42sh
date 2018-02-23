/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 14:39:27 by pchadeni          #+#    #+#             */
/*   Updated: 2018/02/23 12:32:14 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_ast	*init_ast(void)
{
	t_ast	*tmp;

	if (!(tmp = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	tmp->lex = NULL;
//	tmp->value = NULL;
	tmp->parent = NULL;
	tmp->left = NULL;
	tmp->right = NULL;
	return (tmp);
}
