/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_dollar_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 09:50:37 by hfouques          #+#    #+#             */
/*   Updated: 2018/04/10 09:50:40 by hfouques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static void			replace_dol_in_str(t_comp *comp, char *dollar, char *value)
{
	char *new;
	char *prefix;
	char *suffix;

	prefix = ft_strsub(comp->str, 0, ft_strlen(comp->str) - ft_strlen(dollar));
	suffix = ft_strchr(dollar, '/');
	new = ft_strjoin_infinite(3, prefix, value, suffix);
	ft_strdel(&comp->str);
	ft_strdel(&prefix);
	ft_strdel(&value);
	comp->str = new;
}

static char			*get_to_search_value(char *to_search, t_edit *edit)
{
	char *value;
	char *ret;

	if (!(value = ft_getenv(&edit->env, to_search)))
		value = ft_getenv(&edit->loc, to_search);
	ret = ft_strdup(value);
	return (ret);
}

static char			*get_new_dollar_value(char *str, t_edit *edit)
{
	char *end;
	char *tmp;
	char *ret;

	end = ft_strchr(str, '/');
	if (end)
	{
		tmp = ft_strsub(str, 1, ft_strlen(str) - ft_strlen(end) - 1);
		if (!is_in_env(edit->env, tmp) && !is_in_env(edit->loc, tmp))
			ret = NULL;
		else
			ret = get_to_search_value(tmp, edit);
		ft_strdel(&tmp);
		return (ret);
	}
	return (NULL);
}

void				add_dollar_in_str(t_comp *comp, t_edit *edit)
{
	char *tmp;
	char *saved;
	char *new_value;

	saved = ft_strdup(comp->str);
	tmp = saved;
	while ((tmp = ft_strchr(tmp, '$')))
	{
		new_value = get_new_dollar_value(tmp, edit);
		if (new_value)
			replace_dol_in_str(comp, tmp, new_value);
		tmp++;
	}
	ft_strdel(&saved);
	return ;
}
