/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:33:20 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/28 11:12:29 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

void	from_list_to_comp(t_line *cur, t_comp *comp)
{
	comp->cmd = get_cmd_from_cur(cur);
	cmd->pos = cur->index + 1;
	char		*str;
	char		*dir;
}