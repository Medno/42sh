/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 18:04:49 by hlely             #+#    #+#             */
/*   Updated: 2018/03/17 12:09:58 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		create_loc(t_init *init)
{
	uid_t	uid;
	char	*name;
	char	*value;

	uid = getuid();
	name = "UID";
	value = ft_itoa(uid);
	ft_setenv(&init->loc_env, name, value);
	ft_strdel(&value);
}

void		init_all(char **env, t_init *init)
{
	struct termios	current;

	tcgetattr(STDIN_FILENO, &current);
	init->str = NULL;
	init->stop = 0;
	init->dollar = 0;
	init->lex = NULL;
	init->ast = NULL;
	init->loc_env = NULL;
	init->pid_list = NULL;
	init->new_env = (env) ? create_env(env) : NULL;
	insert_env_start(&init->new_env);
	init->historic = new_hist();
	init->current = current;
	create_loc(init);
}
