/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 10:55:49 by pchadeni          #+#    #+#             */
/*   Updated: 2018/04/10 15:27:46 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

extern int		g_status;

static int		step_3(t_init *init, t_ast *ast, int quote_again)
{
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
			if (!init->dollar)
				quote_again = exec_start(ast, init);
		}
	}
	clean_ast(&init->ast);
	del_lex(init->lex);
	del_heredoc();
	return (quote_again);
}

int				main_step_2(t_init *init)
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
	return (step_3(init, ast, quote_again));
}

static int		step_1(t_init init)
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
			main_step_2(&init);
		if (ret == 1 || init.stop)
			ft_exit(&init, NULL);
		ft_strdel(&init.str);
	}
}

int				main(int ac, char **av, char **environ)
{
	t_init			init;

	g_status = 0;
	if (!isatty(STDIN_FILENO))
		return (read_stdin(environ));
	init_all(environ, &init);
	g_in = &init;
	signal(SIGSEGV, (void (*)(int))catch_and_reset);
	signal(SIGABRT, (void (*)(int))catch_and_reset);
	signal(SIGBUS, (void (*)(int))catch_and_reset);
	signal(SIGFPE, (void (*)(int))catch_and_reset);
	signal(SIGTRAP, (void (*)(int))catch_and_reset);
	signal(SIGHUP, (void (*)(int))catch_and_reset);
	signal(SIGTERM, (void (*)(int))catch_and_reset);
	step_1(init);
	(void)ac;
	(void)av;
	return (0);
}
