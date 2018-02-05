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

	tcgetattr(STDIN_FILENO, &current);
	ft_cfmakeraw(&current);
	new_env = create_env(environ);
	insert_env_start(&new_env);
	while (1)
	{
		put_path(&new_env);
	}
	ft_cfmakedefault(&current);
	return (0);
}
