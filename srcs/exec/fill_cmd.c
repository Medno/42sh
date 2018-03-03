/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:57:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/02 14:41:23 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_type	g_type[] =
{
	{REDIR			, &add_redir_token	},
	{REDIR_FILE		, &add_redir_file	},
	{ARG			, &add_arg			},
	{SEPAR			, &stop_fill		},
	{SEMI_COLON		, &stop_fill		},
	{0				, 0					},
};

int		add_redir_token(t_cmd *cmd, t_lex *lex)
{
	t_redir *tmp;

	(void)lex;
	if (cmd->redir == NULL)
	{
		cmd->redir = init_redir();
		cmd->redir->token = ft_strdup("Fonction ADD_REDIR_TOKEN a mettre en place\n");
	}
	else
	{
		tmp = cmd->redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->file = ft_strdup("Fonction ADD_REDIR_TOKEN a mettre en place\n");
	}
	return (0);
}

int		add_redir_file(t_cmd *cmd, t_lex *lex)
{
	t_redir *tmp;

	(void)lex;
	if (cmd->redir == NULL)
	{
		cmd->redir = init_redir();
		cmd->redir->file = ft_strdup("Fonction ADD_REDIR_FILE a mettre en place\n");
	}
	else
	{
		tmp = cmd->redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->file = ft_strdup("Fonction ADD_REDIR_FILE a mettre en place\n");
	}
	return (0);	
}
int		add_arg(t_cmd *cmd, t_lex *lex)
{
	(void)lex;
	cmd->arg = ft_memalloc(sizeof(char *) * 2);
	cmd->arg[0] = ft_strdup("Fonction ADD_ARG a mettre en place\n");
	return (0);
}

int		stop_fill(t_cmd *cmd, t_lex *lex)
{
	cmd->separ = ft_strdup("Fonction STOP_FILL a mettre en place\n");
	(void)lex;
	return (1);
}

int		is_token(int value, t_token token)
{
	(void)token;
	(void)value;
	return (1);
}

t_lex 	*fill_cmd(t_cmd *cmd, t_lex *lex)
{
	t_lex	*tmp;
	int		i;
	int		ret;

	tmp = lex;
	while (tmp)
	{
		i = 0;
		while (g_type[i].value != 0 && ret != 1)
		{
			if (is_token(g_type[i].value, lex->token))
				ret = g_type[i].f(cmd, lex);
			i++;
		}
		tmp = tmp->next;
	}
	return (tmp);
}
