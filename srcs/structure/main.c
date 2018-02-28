/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 16:48:01 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/28 11:13:48 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			init_all(char **env, t_init *init)
{
	t_lex			*lex;
	t_env			*new_env;
	t_hist			*historic;
	char			*str;
	struct termios	current;

	tcgetattr(STDIN_FILENO, &current);
	new_env = create_env(env);
	insert_env_start(&new_env);
	historic = NULL;
	historic = new_hist();
	str = NULL;
	init->str = str;
	lex = NULL;
	init->lex = lex;
	init->new_env = new_env;
	init->historic = historic;
	init->current = current;
}

int				main(int ac, char **av, char **environ)
{
	int				ret;
	int				len_prompt;
	t_init			init;

	if (!init_termcaps())
		return (0);
	init_all(environ, &init);
	while (42)
	{
		len_prompt = put_path(&init.new_env);
		ft_cfmakeraw(&init.current);
		ret = ft_line_edition(&init.str, len_prompt, &init.historic);
		ft_cfmakedefault(&init.current);
		init.lex = lexer(init.str);
		parser(init.lex);
		ft_strdel(&init.str);
	}
	hist_to_file(init.historic);
	(void)ac; // FOR FURTHER USE (DEBUG AND SHELL OPTIONS OR SCRIPTS)
	(void)av;
	return (0);
}
