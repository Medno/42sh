/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_tilde_expansion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 09:52:15 by hfouques          #+#    #+#             */
/*   Updated: 2018/04/10 09:52:17 by hfouques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static void			replace_tilde_in_str(t_comp *comp, char *new_tild)
{
	char *new;

	new = ft_strjoin(new_tild, comp->str + 1);
	ft_strdel(&comp->str);
	comp->str = new;
}

static char			*get_home_value(t_edit *edit)
{
	char *home;
	char *tmp;

	if (!(home = ft_getenv(&edit->env, "HOME")))
		home = ft_getenv(&edit->loc, "HOME");
	if (home)
		tmp = ft_strdup(home);
	else
		tmp = ft_strdup("~");
	return (tmp);
}

static int			has_prefix(char *str)
{
	char *tmp;

	tmp = str + 1;
	if (tmp && !(*tmp))
		return (2);
	if (tmp && *tmp && *tmp != '/')
		return (0);
	return (1);
}

void				add_tild_in_str(t_comp *comp, t_edit *edit)
{
	char *home;

	home = get_home_value(edit);
	if (has_prefix(comp->str) == 1)
		replace_tilde_in_str(comp, home);
	else if (!has_prefix(comp->str))
		replace_tilde_in_str(comp, "/Users/");
	ft_strdel(&home);
}
