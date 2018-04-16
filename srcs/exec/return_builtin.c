/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 14:16:26 by hlely             #+#    #+#             */
/*   Updated: 2018/04/14 14:16:46 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		return_builtin(t_ast *ast)
{
	while (ast && ast->right)
		ast = ast->right;
	if (ast->cmd && ast->cmd->arg && ast->cmd->arg[0])
		if (is_builtin(ast->cmd->arg[0]))
			return (1);
	return (0);
}
