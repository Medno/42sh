/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:32:20 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/21 18:48:33 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static char		**do_expansion(t_init *init, char *str, char **res)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = NULL;
	tmp = ft_addstr_tab(tmp, str);
	if (tmp[0])
	{
		if (tmp[0][0] == '~')
			tmp[0] = exp_tilde(init, tmp[0], ft_strlen(tmp[0]));
		tmp = (ft_strchr(tmp[0], '$')) ? exp_dollar(init, tmp) : tmp;
		while (tmp[i])
		{
			tmp[i] = delete_esc(tmp[i], ft_strlen(tmp[i]));
			i++;
		}
		i = 0;
		while (tmp[i])
		{
			res = ft_addstr_tab(res, tmp[i]);
			i++;
		}
		ft_freetab(tmp);
	}
	return (res);
}

static t_cmd	*begin_expansion(t_init *init, t_cmd *cmd)
{
	char	**res;
	int		i;

	i = 0;
	res = NULL;
	while (cmd->arg[i])
	{
		res = do_expansion(init, cmd->arg[i], res);
		i++;
	}
	ft_freetab(cmd->arg);
	cmd->arg = res;
	return (cmd);
}

void			ast_expansion(t_init *init, t_ast *ast)
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
