/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:32:20 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/21 16:05:20 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*do_expansion(t_init *init, char *str, char ***tab, int *index)
{
	char	*check_expans;

	check_expans = ft_strdup(str);
	ft_strdel(&str);
	(*tab)[*index] = check_expans;
	if (check_expans[0] == '~')
		check_expans = exp_tilde(init, check_expans,
				ft_strlen(check_expans));
	if (ft_strchr(check_expans, '$'))
		check_expans = dollar_exp(init, check_expans, tab, index);
	check_expans = delete_esc(check_expans, ft_strlen(check_expans));
	return (check_expans);
}

t_cmd	*begin_expansion(t_init *init, t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*redir;
	int		i;

	tmp = cmd;
	redir = cmd->redir;
	i = 0;
	while (tmp && tmp->arg && tmp->arg[i])
	{
		tmp->arg[i] = do_expansion(init, tmp->arg[i], &tmp->arg, &i);
		i++;
	}
	while (redir)
	{
		if (redir->file)
			redir->file = do_expansion(init, redir->file, &tmp->arg, &i);
		redir = redir->next;
	}
	return (tmp);
}

void	ast_expansion(t_init *init, t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->left)
		ast_expansion(init, ast->left);
	if (ast->right)
		ast_expansion(init, ast->right);
	if (ast->cmd)
		ast->cmd = begin_expansion(init, ast->cmd);
}
