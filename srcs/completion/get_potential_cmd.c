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

static char		*get_next_path(char *str)
{
	int		i;
	int		start;
	char	*tmp;

	if (!(str))
		return (NULL);
	i = 0;
	start = 0;
	tmp = str;
	if (*tmp == ':')
	{
		start++;
		tmp++;
	}
	while (*tmp && *(tmp + 1) && *(tmp + 1) != ':')
	{
		tmp++;
		i++;
	}
	tmp = ft_strsub(str, start, i + 1);
	tmp = ft_strjoindel(tmp, "/");
	return (tmp);
}

static int		ft_nbr_path(char *str)
{
	char	*tmp;
	int		i;

	if (!(str))
		return (0);
	tmp = str;
	i = 1;
	while (*tmp)
	{
		if (*tmp == ':' && *(tmp + 1) && *(tmp + 1) != ':')
			i++;
		tmp++;
	}
	return (i);
}

static char		**comp_get_all_path(t_edit *edit)
{
	int		i;
	char	**tabl;
	char	*tmp;

	tmp = ft_getenv(&edit->env, "PATH");
	if (!tmp)
		tmp = ft_getenv(&edit->loc, "PATH");
	if (!(tabl = malloc(sizeof(char *) * (ft_nbr_path(tmp) + 1))))
		return (NULL);
	i = 0;
	while (i < ft_nbr_path(tmp))
	{
		tabl[i] = get_next_path(tmp);
		if (*tmp && *tmp == ':')
			tmp++;
		while (*tmp && *tmp != ':')
			tmp++;
		i++;
	}
	tabl[i] = NULL;
	return (tabl);
}

static int		comp_is_pot_cmd(char *lex, char *str, char *path)
{
	struct	stat sb;
	char	*abs_path;
	int		ret;

	ret = 0;
	if (path)
		abs_path = ft_strjoin_infinite(3, path, "/", lex);
	else
		abs_path = ft_strdup(lex);
	if (stat(abs_path, &sb) == 0 && (sb.st_mode & S_IXOTH) && !S_ISDIR(sb.st_mode))
    {
		if (str == NULL || ft_strlen(str) == 0)
			ret = 0;
		else if (ft_strncmp(lex, str, ft_strlen(str)) == 0)
			ret = 1;
	}
	ft_strdel(&abs_path);
	return (ret);
}

void			comp_get_pot_cmd(t_comp *comp, t_edit *edit)
{
	t_lcomp			*new;
	DIR				*dir;
	struct dirent	*info;
	char			**all_path;
	int				i;

	all_path = comp_get_all_path(edit);
	i = 0;
	while (all_path[i])
	{
		dir = opendir(all_path[i]);
		while (dir && (info = readdir(dir)))
		{
			if (comp_is_pot_cmd(info->d_name, comp->str, all_path[i]))
			{
				new = init_t_lcomp();
				new->cmd = ft_strdup(info->d_name);
				comp->list = lcomp_push_back(comp->list, new);
			}
		}
		closedir(dir);
		i++;
	}
	ft_freetab(all_path);
	comp_add_pot_builtin(comp);
}
