/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 11:52:05 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/21 18:26:07 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob.h"

static void	wild_path(t_glpath **elem)
{
	(void)elem;
}

static int	count_wild(char *path, int dot)
{
	DIR				*dir;
	struct dirent	*directory;
	int				i;

	dir = opendir(path);
	i = 0;
	while ((directory = readdir(dir)))
	{
		if (*(directory->d_name) != '.' && !dot)
			i++;
		else if (*directory->d_name == '.' && dot)
			i++;
	}
	closedir(dir);
	return (i);
}

static void	expand_wild(t_glpath **el)
{
	if (ft_strchr((*el)->str, '/'))
		wild_path(el);
	else
	{
		if (*(*el)->str == '.')
			(*el)->elem.nb = count_wild(".", 1);
		else
			(*el)->elem.nb = count_wild(".", 0);
	}
}

void	expand_list(t_glpath **list)
{
	t_glpath	*tmp;
	int			ret;

	tmp = *list;
	while (tmp)
	{
		if ((ret = check_glob(tmp->str)))
		{
			if (ret == 1)
				expand_wild(&tmp);
			else if (ret == 2)
				;//brackets solid
			else if (ret == 3)
				;//brackets
		}
		tmp = tmp->next;
	}
}
