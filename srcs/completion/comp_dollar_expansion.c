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

void			replace_dollar_in_str(t_comp *comp, char *dollar, char *new_value)
{
	char *new;
	char *prefix;
	char *suffix;

	prefix = ft_strsub(comp->str, 0, ft_strlen(comp->str) - ft_strlen(dollar));
	suffix = ft_strchr(dollar, '/');
	new = ft_strjoin_infinite(3, prefix, new_value, suffix);
	ft_strdel(&comp->str);
	ft_strdel(&prefix);
	ft_strdel(&new_value);
	comp->str = new;
}


char			*get_to_search_value(char *to_search, t_edit *edit)
{
	char *value;
	char *ret;

	if (!(value = ft_getenv(&edit->env, to_search)))
		value = ft_getenv(&edit->loc, to_search);
	ret = ft_strdup(value);
	return (ret);
}

char			*get_new_dollar_value(char *str, t_edit *edit)
{
	char *end;
	char *to_search;
	char *ret;

	end = ft_strchr(str, '/');
	if (end)
	{
		to_search = ft_strsub(str, 1, ft_strlen(str) - ft_strlen(end) - 1);
		if (!is_in_env(edit->env, to_search) && !is_in_env(edit->loc, to_search))
			ret = NULL;
		else
			ret = get_to_search_value(to_search, edit);
		ft_strdel(&to_search);
		return (ret);
	}
	return (NULL);
}

char			*go_to_next_dollar(char *str)
{
	char *tmp;

	if (!str)
		return (NULL);
	tmp = str;
	while (tmp && *tmp)
	{
		if (*tmp == '$')
			return (tmp);
		tmp++;
	}
	return (NULL);
}

void			add_dollar_in_str(t_comp *comp, t_edit *edit)
{
	char *tmp;
	char *saved;
	char *new_value;

	saved = ft_strdup(comp->str);
	tmp = saved;
	while ((tmp = go_to_next_dollar(tmp)))
	{
		new_value = get_new_dollar_value(tmp, edit);
		if (new_value)
			replace_dollar_in_str(comp, tmp, new_value);
		tmp++;
	}
	ft_strdel(&saved);
	return ;
}
