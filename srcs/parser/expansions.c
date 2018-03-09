/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 16:37:15 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/09 18:08:17 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	expansion_expr(t_init *init, t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;
	int		j;

	i = 0;
	tmp = cmd;
	while (tmp->arg[i])
	{
		j = 0;
		while (tmp->arg[i][j] && !is_esc(tmp->arg[i][j]))
			j++;
		if (tmp->arg[i][j])
			tmp->arg[i] = delete_esc(init, tmp->arg[i], ft_strlen(tmp->arg[i]));
		ft_putendl(tmp->arg[i]);
		i++;
	}
}

void	word_exp(t_init *init, t_ast *ast)
{
	if (ast->left)
		word_exp(init, ast->left);
	if (ast->right)
		word_exp(init, ast->right);
	if (ast->cmd)
		expansion_expr(init, ast->cmd);
}
