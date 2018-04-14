/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 16:21:24 by hlely             #+#    #+#             */
/*   Updated: 2018/04/13 15:52:08 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	line_edit(char **line, int len_prompt, t_init *init)
{
	int	ret;

	ft_cfmakeraw(&init->current);
	ret = ft_line_edition(line, len_prompt, &init->historic, *init);
	ft_cfmakedefault(&init->current);
	g_status = (ret == 3) ? 1 : g_status;
	return (ret);
}
