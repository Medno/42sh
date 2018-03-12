/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 16:21:24 by hlely             #+#    #+#             */
/*   Updated: 2018/03/12 14:16:31 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*line_edit(int len_prompt, t_init *init)
{
	char	*line_tmp;

	line_tmp = NULL;
	ft_cfmakeraw(&init->current);
	ft_line_edition(&line_tmp, len_prompt, &init->historic, init->new_env);
	ft_cfmakedefault(&init->current);
	return (line_tmp);
}
