/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_get_word_to_complete.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 09:51:10 by hfouques          #+#    #+#             */
/*   Updated: 2018/04/10 09:51:11 by hfouques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static int		get_start(t_comp *comp)
{
	char	*tmp;
	int		i;

	i = comp->pos - 1;
	tmp = comp->cmd;
	if (is_delimiteur(tmp, i) && i != 0 && is_delimiteur(tmp, i - 1))
		return (i);
	while (i > 0)
	{
		i--;
		if (is_delimiteur(tmp, i))
			break ;
	}
	if (is_delimiteur(tmp, i))
		i++;
	return (i);
}

static size_t	get_len(t_comp *comp, int start)
{
	char	*tmp;
	size_t	ret;

	tmp = comp->cmd + start;
	ret = 0;
	if (start == comp->pos - 1)
		return (0);
	while (*tmp && !is_delimiteur(tmp, ret))
	{
		ret++;
		if ((int)start + (int)ret == comp->pos - 1)
			break ;
	}
	return (ret);
}

/*
**	On veut recuperer la string a modifier par completion
**	Càd isoler [string a comp] dans "[prefix] [string a comp][suffix]"
**	On isole le debut et la taille de la string start pour effectuer un strsub
*/

void			get_word_to_complete(t_comp *comp)
{
	int		start;
	size_t	len;

	if (comp->cmd)
	{
		start = get_start(comp);
		len = get_len(comp, start);
		comp->str = ft_strsub(comp->cmd, start, len);
	}
}
