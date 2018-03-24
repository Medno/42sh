/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_comp_cmd.c                                      :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <hfouques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 18:59:14 by hfouques          #+#    #+#             */
/*   Updated: 2017/02/20 18:20:51 by hfouques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static int	comp_is_pot_local(char *name, char *str)
{
	int		ret;

	ret = 0;
	if (str == NULL || ft_strlen(str) == 0)
		ret = 1;
	else if (ft_strncmp(name, str, ft_strlen(str)) == 0)
		ret = 1;
	return (ret);
}

static void		add_pot_local(t_comp *comp, t_env *env)
{
	t_env *tmp;
	t_lcomp *new;
	
	tmp = env;
	while (tmp)
	{
		if (comp_is_pot_local(tmp->name, comp->str + 1))
		{
			new = init_t_lcomp();
			new->cmd = ft_strjoin("$", tmp->name);
			comp->list = lcomp_push_back(comp->list, new);
		}
		tmp = tmp->next;
	}
}

void		comp_get_pot_local(t_comp *comp, t_edit *edit)
{
	add_pot_local(comp, edit->env);
	add_pot_local(comp, edit->loc);
}