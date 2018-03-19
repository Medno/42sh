/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_cmd.c                                       :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <hfouques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 18:59:14 by hfouques          #+#    #+#             */
/*   Updated: 2017/02/20 18:20:51 by hfouques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

int		is_delimiteur(char c)
{
	if (c == ' ' || c == ':' || c == '>' || c == '=' || c == '<')
		return (1);
	return (0);
}

int		comp_is_first_word(t_comp *comp)
{
	int i;

	i = 0;
// Dodge ESPACE au debut
	while (comp->cmd[i] && comp->cmd[i] == ' ')
		i++;
// On parcourt le premier mot
	while (comp->cmd[i] && !is_delimiteur(comp->cmd[i]))
		i++;

	if (i > comp->pos - 2)
		return (1);
	return (0);
}

int		comp_has_slash(char *str)
{
	if (ft_strchr(str, '/'))
		return (1);
	return (0);
}


char	*comp_go_to_last_slash(char *str)
{
	char *tmp;
	char *ret;

	tmp = str;
	ret = NULL;
	while (tmp && *tmp)
	{
		if (*tmp == '/')
			ret = tmp;
		tmp++;
	}
	return (ret);
}

