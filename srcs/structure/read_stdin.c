/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 09:33:29 by hlely             #+#    #+#             */
/*   Updated: 2018/04/10 10:51:54 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		read_stdin(char **environ)
{
	t_init	init;
	char	*line;

	line = NULL;
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		init_all(environ, &init);
		init.str = line;
		main_step_2(&init);
		hist_to_file(init.historic);
		free_list(&init.new_env);
		free_list(&init.loc_env);
		ft_strdel(&line);
	}
	return (0);
}
