/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 16:48:01 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/07 10:54:15 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			init_all(char **env, t_init *init)
{
	struct termios	current;

	tcgetattr(STDIN_FILENO, &current);
	init->str = NULL;
	init->lex = NULL; 
	init->cmd = NULL;
	init->new_env = create_env(env);
	insert_env_start(&init->new_env);
	init->historic = new_hist();
	init->current = current;
}

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
	exec_start(init);
	return (quote_again);
}

int				main(int ac, char **av, char **environ)
{
	int				len_prompt;
	t_init			init;

	if (!isatty(STDIN_FILENO))
		return (0);
	init_all(environ, &init);
	while (42)
	{
		len_prompt = put_path(&init.new_env);
		ft_cfmakeraw(&init.current);
		if (!ft_line_edition(&init.str, len_prompt, &init.historic, init.new_env))
			ft_exit(&init);
		ft_cfmakedefault(&init.current);
		step_2(&init);
		ft_strdel(&init.str);
	}
	(void)ac; // FOR FURTHER USE (DEBUG AND SHELL OPTIONS OR SCRIPTS)
	(void)av;
	return (0);
}
