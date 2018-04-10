/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_potential_directory.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 09:53:39 by hfouques          #+#    #+#             */
/*   Updated: 2018/04/10 09:53:40 by hfouques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static int		is_pot_dir(char *dir, char *str)
{
	int		ret;

	ret = 0;
	if (str == NULL || *str == 0)
	{
		if (*dir == '.')
			ret = 0;
		else
			ret = 1;
	}
	else if (ft_strncmp(dir, str, ft_strlen(str)) == 0)
		ret = 1;
	return (ret);
}

static int		has_exec_rights(char *dir_to_open, char *d_name)
{
	struct stat	sb;
	int			ret;
	char		*file_path;

	file_path = ft_strjoin_infinite(3, dir_to_open, "/", d_name);
	if (stat(file_path, &sb) != 0)
		ret = 0;
	else
	{
		if (sb.st_mode & S_IXUSR)
			ret = 1;
		else
			ret = 0;
	}
	ft_strdel(&file_path);
	return (ret);
}

void			comp_get_pot_dir_exec(t_comp *comp)
{
	DIR				*dir;
	struct dirent	*info;
	t_lcomp			*new;

	if ((dir = opendir(comp->dir)))
	{
		while ((info = readdir(dir)))
		{
			if (is_pot_dir(info->d_name, comp->str)
				&& has_exec_rights(comp->dir, info->d_name))
			{
				new = init_t_lcomp();
				new->cmd = ft_strdup(info->d_name);
				comp->list = lcomp_push_back(comp->list, new);
			}
		}
		closedir(dir);
	}
}

void			comp_get_pot_dir(t_comp *comp)
{
	DIR				*dir;
	struct dirent	*info;
	t_lcomp			*new;

	if ((dir = opendir(comp->dir)))
	{
		while ((info = readdir(dir)))
		{
			if (is_pot_dir(info->d_name, comp->str))
			{
				new = init_t_lcomp();
				new->cmd = ft_strdup(info->d_name);
				comp->list = lcomp_push_back(comp->list, new);
			}
		}
		closedir(dir);
	}
}
