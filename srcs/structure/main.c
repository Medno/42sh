/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 10:55:49 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/16 12:22:12 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

extern int		g_status;
extern int		g_oldstatus;

static int		step_3(t_init *init, t_ast *ast, int quote_again)
{
	if (ast)
	{
		while (ast && ast->value == SEMI)
		{
			quote_again = exec_start(ast->left, init);
			ast = ast->right;
		}
		if (ast && ast->value != SEMI)
			quote_again = exec_start(ast, init);
	}
	clean_ast(&init->ast);
	del_lex(&init->lex);
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

static void		step_1(t_init init)
{
	int		ret;
	int		len_prompt;

	while (42)
	{
		init.dollar = 0;
		len_prompt = put_path(&init);
		ft_cfmakeraw(&init.current);
		ret = ft_line_edition(&init.str, len_prompt, &init.historic, init);
		g_status = (ret == 3) ? 1 : g_status;
		ft_cfmakedefault(&init.current);
		init.historic = cleanup_nl_hist(&init.historic);
		if (!ret && init.str && !ft_strequ(init.str, "\n"))
			main_step_2(&init);
		if (ret == 1 || init.stop)
			ft_exit(&init, NULL);
		ft_strdel(&init.str);
	}
}

int				backup_closed(void)
{
	struct stat	buf;
	int			fd1;
	int			fd2;

	fd1 = dup(STDOUT_FILENO);
	fd2 = dup(STDERR_FILENO);
	if (fstat(fd1, &buf) == -1 || fstat(fd2, &buf) == -1)
	{
		ft_printf_fd(STDIN_FILENO, "42sh: Bad file descriptor\n");
		return (1);
	}
	close(fd1);
	close(fd2);
	return (0);
}

int				main(int ac, char **av, char **environ)
{
	t_init			init;

	g_status = 0;
	if (!isatty(STDIN_FILENO) || backup_closed())
		return (1);
	if (init_all(environ, &init) == 0)
		return (1);
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
