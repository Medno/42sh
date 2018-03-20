/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:32:20 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/20 18:43:46 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*do_expansion(t_init *init, char *str)
{
	char	*check_expans;

	check_expans = ft_strdup(str);
	if (check_expans[0] == '~')
		check_expans = exp_tilde(init, check_expans,
				ft_strlen(check_expans));
	if (ft_strchr(check_expans, '$'))
		check_expans = dollar_exp(init, check_expans);
	check_expans = delete_esc(check_expans, ft_strlen(check_expans));
	ft_strdel(&str);
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
		tmp->arg[i] = do_expansion(init, tmp->arg[i]);
		i++;
	}
	//Philippe faudrait que tu valides ca, y'avait un pb avec les expansions dans les redirs
	while (redir)
	{
		if (redir->file)
			redir->file = do_expansion(init, redir->file);
		redir = redir->next;
	}
	//jusqu'ici
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
