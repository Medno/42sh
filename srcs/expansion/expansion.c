/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:32:20 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/16 11:10:46 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void			put_in_buffer(char buf[], char c)
{
	int	len;

	len = ft_strlen(buf);
	buf[len] = c;
}

static char		**concat_res(char **res, char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		res = ft_addstr_tab(res, tmp[i]);
		i++;
	}
	return (res);
}

static char		**do_expansion(t_init *init, char *str, char **res)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = NULL;
	tmp = ft_addstr_tab(tmp, str);
	if (tmp && tmp[0])
	{
		if (tmp[0][0] == '~')
			tmp[0] = exp_tilde(init, tmp[0], ft_strlen(tmp[0]));
		if (ft_strchr(tmp[0], '~'))
			tmp[0] = assign_tilde(init, tmp[0]);
		tmp = (ft_strchr(tmp[0], '$')) ? exp_dollar(init, tmp) : tmp;
		while (tmp[i])
		{
			tmp[i] = delete_esc(tmp[i], ft_strlen(tmp[i]));
			i++;
		}
		res = concat_res(res, tmp);
	}
	ft_freetab(tmp);
	return (res);
}

t_cmd			*begin_expansion(t_init *init, t_cmd *cmd)
{
	char	**res;
	char	**res_redir;
	int		i;

	i = 0;
	res = NULL;
	res_redir = NULL;
	while (cmd->arg && cmd->arg[i])
	{
		res = do_expansion(init, cmd->arg[i], res);
		i++;
	}
	if (cmd->redir && cmd->redir->file && cmd->redir->file[0])
	{
		res_redir = do_expansion(init, cmd->redir->file[0], res_redir);
		ft_freetab(cmd->redir->file);
		cmd->redir->file = res_redir;
	}
	ft_freetab(cmd->arg);
	cmd->arg = res;
	return (cmd);
}
