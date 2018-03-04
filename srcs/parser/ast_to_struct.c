#include "parser.h"

t_cmd	*init_cmd_p(void)
{
	t_cmd	*cmd;

	if (!(cmd = (t_cmd *)malloc(sizeof(cmd))))
		return (NULL);
	cmd->v_cmd = NULL;
	if (!(cmd->arg = (char **)malloc(sizeof(cmd->arg))))
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

	i = 0;
	if (cmd->v_cmd)
		ft_printf("Commande : |%s|\n", cmd->v_cmd);
	if (cmd->arg)
	{
		while (cmd->arg[i])
		{
			ft_printf("Parametre %d : |%s|\n", i, cmd->arg[i]);
			i++;
		}
	}
	while (cmd->redir)
	{
		ft_printf("Valeur du fd_in : |%d|\n", cmd->redir->fd_in);
		ft_printf("Valeur du token : |%s|\n", cmd->redir->token);
		if (cmd->redir->file)
			ft_printf("Valeur du fd_out : |%s|\n", cmd->redir->fd_out);
		else
			ft_printf("Valeur du fd_out : |%d|\n", cmd->redir->fd_out);
		cmd->redir = cmd->redir->next;
	}
}

t_redir	*put_redir(t_ast *ast)
{
	t_redir	*redir;

	if (!ast)
		return (NULL);
	redir = init_redir();
	if (ft_strequ(ast->value, "io"))
	{
		redir->token = ft_strdup(ast->left->value);
		if (ast->left->value[0] == '>')
			redir->fd_in = 1;
		else
			redir->fd_in = 0;
		if (is_number(ast->right->value))
			redir->fd_out = ft_atoi(ast->right->value);
		else
			redir->file = ft_strdup(ast->right->value);
	}
	else
	{
		redir->token = ft_strdup(ast->left->left->value);
		redir->fd_in = ft_atoi(ast->value);
		if (is_number(ast->left->right->value))
			redir->fd_out = ft_atoi(ast->left->right->value);
		else
			redir->file = ft_strdup(ast->left->right->value);
		
	}
	return (redir);
}

t_cmd	*ast_to_sentence(t_cmd *cmd, t_ast *ast)
{
	int	sep;

	if (!ast)
		return (cmd);
	sep = (ft_strequ(ast->value, "&&") || ft_strequ(ast->value, "||")) ? 1 : 0;
	if (ft_strequ(ast->value, "io_redirect"))
	{
		if (cmd->redir)
			cmd->redir->next = put_redir(ast->right);
		else
			cmd->redir = put_redir(ast->right);
		return ((cmd = ast_to_sentence(cmd, ast->left)));
	}
	else if (sep)
	{
		cmd->separ = ft_strdup(ast->value);
		cmd = ast_to_sentence(cmd, ast->left);
		cmd->next = init_cmd_p();
		cmd->next = ast_to_sentence(cmd->next, ast->right);
	}
	if (!sep)
	{
		if (!cmd->v_cmd)
			cmd->v_cmd = ft_strdup(ast->value);
		else
			cmd->arg = ft_addstr_tab(cmd->arg, ast->value);
	}
	return ((cmd = ast_to_sentence(cmd, ast->left)));
}

t_cmd	*ast_to_struct(t_ast *ast)
{
	t_cmd	*cmd;

	if (!ast)
		return (NULL);
	cmd = init_cmd_p();
	if (ft_strequ(ast->value, ";") || ft_strequ(ast->value, "&"))
		cmd->next_semi = ast_to_struct(ast->right);
	else
		cmd = ast_to_sentence(cmd, ast);
	return (cmd);
}
