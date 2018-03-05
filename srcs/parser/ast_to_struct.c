/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 11:18:45 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/05 13:24:44 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*init_cmd_p(void)
{
	t_cmd	*cmd;

	if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->arg = NULL;
	cmd->redir = NULL;
	cmd->separ = NULL;
	cmd->next = NULL;
	cmd->next_semi = NULL;
	return (cmd);
}

void	print_cmd(t_cmd *cmd)
{
	int	i;
	t_cmd	*tmp;
	t_cmd	*tmp_2;
	t_redir	*leak;

	tmp = cmd;
	while (tmp)
	{
		ft_printf("Nouvelle commande :\n");
		tmp_2 = tmp;
		while(tmp_2)
		{
			i = 0;
			if (tmp_2->arg)
			{
				while (tmp_2->arg[i])
				{
					ft_printf("Parametre %d : |%s|\n", i, tmp_2->arg[i]);
					i++;
				}
			}
			if (tmp_2->separ)
				ft_printf("Separateur : |%s|\n", tmp_2->separ);
			leak = tmp_2->redir;
			while (leak)
			{
				ft_printf("fd_in : |%d|\ntoken : |%s|\nfd_out : ", leak->fd_in, leak->token);
				if (leak->file)
					ft_putstr(leak->file);
				else
					ft_putnbr(leak->fd_out);
				ft_putchar('\n');
				leak = leak->next;
			}
			tmp_2 = tmp_2->next;
		}
		tmp = tmp->next_semi;
	}
}

t_redir	*put_redir(t_ast *ast)
{
	t_redir	*redir;

	redir = init_redir();
	if (!ast)
		return (NULL);
	if (ft_strequ(ast->value, "io"))
	{
		if (ast->left->value[0] == '>')
			redir->fd_in = 1;
		else
			redir->fd_in = 0;
	}
	else
	{
		redir->fd_in = ft_atoi(ast->value);
		ast = ast->left;
	}
	redir->token = ft_strdup(ast->left->value);
	if (is_number(ast->right->value))
		redir->fd_out = ft_atoi(ast->right->value);
	else
		redir->file = ft_strdup(ast->right->value);
	return (redir);
}

t_cmd	*ast_to_sentence(t_cmd *cmd, t_ast *ast)
{
	if (!ast)
		return (cmd);
	if (ft_strequ(ast->value, "io_redirect"))
	{
		if (cmd->redir)
			cmd->redir->next = put_redir(ast->right);
		else
			cmd->redir = put_redir(ast->right);
		return ((cmd = ast_to_sentence(cmd, ast->left)));
	}
	else if (ft_strequ(ast->value, "&&") || ft_strequ(ast->value, "||") || ft_strequ(ast->value, "|"))
	{
		cmd->separ = ft_strdup(ast->value);
		cmd = ast_to_sentence(cmd, ast->left);
		cmd->next = init_cmd_p();
		cmd->next = ast_to_sentence(cmd->next, ast->right);
		return (cmd);
	}
	cmd->arg = ft_addstr_tab(cmd->arg, ast->value);
	return ((cmd = ast_to_sentence(cmd, ast->left)));
}

t_cmd	*ast_to_struct(t_ast *ast)
{
	t_cmd	*cmd;

	if (!ast)
		return (NULL);
	cmd = init_cmd_p();
	if (ft_strequ(ast->value, ";") || ft_strequ(ast->value, "&"))
	{
		if (ast->right)
			cmd->next_semi = ast_to_struct(ast->right);
		cmd = ast_to_sentence(cmd, ast->left);
	}
	else
		cmd = ast_to_sentence(cmd, ast);
	return (cmd);
}
