/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 15:30:09 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/17 17:34:43 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	free_pathlist(t_path **orig)
{
	t_path	*tmp;

	while (*orig)
	{
		tmp = *orig;
		if (!tmp->next)
		{
			ft_strdel(&tmp->s);
			ft_memdel((void **)&tmp);
			return ;
		}
		tmp = tmp->next;
		tmp->prev->next = NULL;
		ft_strdel(&tmp->prev->s);
		ft_memdel((void **)&(tmp->prev));
		*orig = tmp;
	}
}

t_path	*create_path(char *str)
{
	t_path	*new;

	new = (t_path *)malloc(sizeof(t_path));
	new->s = ft_strdup(str);
	new->perms = 0;
	new->type = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	append_new(t_path **orig, t_path *new)
{
	t_path	*tmp;

	if (!*orig)
		*orig = new;
	else
	{
		tmp = *orig;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

t_path	*new_pathlist(char *str)
{
	t_path	*orig;
	t_path	*new;
	char	**array;
	int		i;

	orig = NULL;
	i = -1;
	if (!(array = ft_strsplit(str, '/')))
		return (NULL);
	while (array[++i])
	{
		new = create_path(array[i]);
		append_new(&orig, new);
	}
	ft_freetab(array);
	return (orig);
}

char	*paste_path(char *p1, char *p2)
{
	int		len1;

	len1 = ft_strlen(p1);
	if (!p1)
		return (ft_strdup(p2));
	if (p1[len1 - 1] == '/' && p2[0] == '/')
		p1[len1 - 1] = 0;
	else if (p1[len1 - 1] != '/' && p2[0] != '/')
		p1 = ft_strjoindel(p1, "/");
	p1 = ft_strjoindel(p1, p2);
	return (p1);
}
