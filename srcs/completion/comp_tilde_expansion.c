/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 16:37:15 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/21 18:49:35 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

void			replace_tilde_in_str(t_comp *comp, char *new_tild)
{
	char *new;

	new = ft_strjoin(new_tild, comp->str + 1);
	ft_strdel(&comp->str);
	comp->str = new;
}


char			*get_home_value(t_edit *edit)
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

static int		has_prefix(char *str)
{
	char *tmp;

	tmp = str + 1;
	if (tmp && !(*tmp))
		return (2);
	if (tmp && *tmp && *tmp != '/')
		return (0);
	return (1);
}

void			add_tild_in_str(t_comp *comp, t_edit *edit)
{
//	[~blbalbalab/suffix]
	char *home;

	home = get_home_value(edit);
	if (has_prefix(comp->str) == 2)
	{
//	 	ft_printf("J'ai reconnu ~ tout seul, je ne fais rien\n");
	 	(void)comp;
//		replace_tilde_in_str(comp, home);
	}
	else if (has_prefix(comp->str) == 1)
	{
		// ft_printf("Il y a un prefix, je remplace ~ par %s\n", home);
		replace_tilde_in_str(comp, home);
	}
	else
	{
		// ft_printf("Il n'y a PAS de prefix, je remplace ~ par %s\n", "/Users");
		replace_tilde_in_str(comp, "/Users/");		
	}
	return ;
}
