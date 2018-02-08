/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 16:48:01 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/08 12:04:46 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

extern char	**environ;

int				main(void)
{
	t_env			*new_env;
	struct termios	current;
	char			*str;
	int				ret;
	int				len_prompt;

	if (!init_termcaps())
		return (0);
	tcgetattr(STDIN_FILENO, &current);
	new_env = create_env(environ);
	insert_env_start(&new_env);
	str = NULL;
	while (1)
	{
		len_prompt = put_path(&new_env);
		ft_cfmakeraw(&current);
		ret = ft_line_edition(&str, len_prompt);
		ft_cfmakedefault(&current);
		ft_strdel(&str);
		if (!ret)
			break ;
	}
	return (0);
}
