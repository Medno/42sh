/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 10:55:49 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/20 19:09:26 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				step_2(t_init *init)
{
	int			quote_again;
	t_ast		*ast;

	quote_again = -1;
	while (quote_again == -1)
	{
		g_quote = 0;
		init->lex = lexer(init->str);
		quote_again = parser(init);
	}
	init->historic = cleanup_nl_hist(&init->historic);
	ast = init->ast;
	if (ast)
	{
		while (ast && ast->value == SEMI)
		{
			ast_expansion(init, ast->left);
			if (!init->dollar)
				quote_again = exec_start(ast->left, init);
			ast = ast->right;
		}
		if (ast && ast->value != SEMI)
		{
			ast_expansion(init, ast);
			//expansion/script/...
			if (!init->dollar)
				quote_again = exec_start(ast, init);
		}
	}
	clean_ast(&init->ast);
	del_lex(init->lex);
	del_heredoc();
	return (quote_again);
}

int				step_1(t_init init)
{
	int		ret;
	int		len_prompt;

	while (42)
	{
		init.dollar = 0;
		len_prompt = put_path(&init.new_env);
		ft_cfmakeraw(&init.current);
		ret = ft_line_edition(&init.str, len_prompt, &init.historic, init);
		ft_cfmakedefault(&init.current);
		init.historic = cleanup_nl_hist(&init.historic);
		if (!ret && init.str)
			step_2(&init);
		if (ret == 1 || init.stop)
			ft_exit(&init, NULL);
		ft_strdel(&init.str);
	}
}

int				setting_terminal(void)
{
	pid_t			shell_pgid;

	shell_pgid = getpid();
	if (setpgid(shell_pgid, shell_pgid) < 0)
	{
		ft_printf_fd(STDERR_FILENO,
				"42sh: can't put the shell in its own process group");
		return (0);
	}
	tcsetpgrp(STDIN_FILENO, shell_pgid);
	return (1);
}

int				main(int ac, char **av, char **environ)
{
	t_init			init;

	if (!isatty(STDIN_FILENO))
		return (0);
	/* if (!setting_terminal()) */
	/* 	return (1); */
	init_all(environ, &init);
	g_in = &init;
	step_1(init);
	(void)ac; // FOR FURTHER USE (DEBUG AND SHELL OPTIONS OR SCRIPTS)
	(void)av;
	return (0);
}
