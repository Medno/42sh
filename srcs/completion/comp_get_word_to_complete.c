/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <hfouques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 18:59:14 by hfouques          #+#    #+#             */
/*   Updated: 2017/02/20 18:20:51 by hfouques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static int		get_start(t_comp *comp)
{
	char *tmp;
	int i;

	i = comp->pos - 1;
	tmp = comp->cmd;
	
//	Cas "commande []"
	if (tmp[i] == ' ' && i != 0 && tmp[i - 1] == ' ')
		return (i);

// Cas "commande[]"
	while (i > 0)
	{
		i--;
		if (tmp[i] == ' ')
			break ;
	}
	if (tmp[i] == ' ')
		i++;
	return (i);
}

static size_t	get_len(t_comp *comp, int start)
{
	char *tmp;
	size_t ret;

	tmp = comp->cmd + start;
	ret = 0;
// Cas "[c]ommande"
	if (start == comp->pos - 1)
		return (0);

// Cas "comma[n]de"
	while (*tmp && *tmp != ' ')
	{
		tmp++;
		ret++;
		if ((int)start + (int)ret == comp->pos - 1)
			break;
	}
	return (ret);
}

void	get_word_to_complete(t_comp *comp)
{
	int start;
	size_t len;

	if (comp->cmd)
	{
		start = get_start(comp);
		len = get_len(comp, start);
		comp->str = ft_strsub(comp->cmd, start, len);
	}
}