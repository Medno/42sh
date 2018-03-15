/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 10:55:49 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/15 16:13:22 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				step_2(t_init *init)
{
	int				quote_again;

	quote_again = -1;
	while (quote_again == -1)
	{
		g_quote = 0;
		init->lex = lexer(init->str);
		quote_again = parser(init);
	}
	init->historic = cleanup_nl_hist(&init->historic);
	if (init->ast)
	{
		while (init->ast && init->ast->value == SEMI)
		{
			//expansion/script/...
			quote_again = exec_start(init->ast->left, init);
			init->ast = init->ast->right;
		}
		if (init->ast && init->ast->value != SEMI)
		{
			//expansion/script/...
			quote_again = exec_start(init->ast, init);
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
		len_prompt = put_path(&init.new_env);
		ft_cfmakeraw(&init.current);
		ret = ft_line_edition(&init.str, len_prompt, &init.historic, init.new_env);
		ft_cfmakedefault(&init.current);
		init.historic = cleanup_nl_hist(&init.historic);
		if (!ret && init.str)
			step_2(&init);
		if (ret == 1 || init.stop)
			ft_exit(&init, NULL);
		ft_strdel(&init.str);
	}
}

int				main(int ac, char **av, char **environ)
{
	t_init			init;

	if (!isatty(STDIN_FILENO))
		return (0);
	init_all(environ, &init);
	g_in = &init;
	step_1(init);
	(void)ac; // FOR FURTHER USE (DEBUG AND SHELL OPTIONS OR SCRIPTS)
	(void)av;
	return (0);
}
