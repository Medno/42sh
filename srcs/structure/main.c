/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 16:48:01 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/31 13:35:12 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

extern char	**environ;

int				main(void)
{
	t_env			*new_env;
	struct termios	current;
	char			*str;
    int             ret;

	if (!init_termcaps())
		return (0);
	tcgetattr(STDIN_FILENO, &current);
	new_env = create_env(environ);
	insert_env_start(&new_env);
    str = NULL;
	while (1)
	{
		put_path(&new_env);
		ft_cfmakeraw(&current);
		ret = ft_line_edition(&str);
		ft_cfmakedefault(&current);
		ft_strdel(&str);
        if (!ret)
            break ;
	}
	return (0);
}
