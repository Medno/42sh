/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_potential_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 09:53:28 by hfouques          #+#    #+#             */
/*   Updated: 2018/04/11 14:13:18 by pchadeni         ###   ########.fr       */
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

	if (!(tmp = ft_getenv(&edit->env, "PATH")))
		tmp = ft_getenv(&edit->loc, "PATH");
	if (!(tabl = malloc(sizeof(char *) * (ft_nbr_path(tmp) + 1))))
		return (NULL);
	i = ft_nbr_path(tmp);
	tabl[i] = NULL;
	while (i > 0)
	{
		i--;
		tabl[i] = get_next_path(tmp);
		if (*tmp && *tmp == ':')
			tmp++;
		while (*tmp && *tmp != ':')
			tmp++;
	}
	return (tabl);
}

static int		comp_is_pot_cmd(char *lex, char *str, char *path)
{
	struct stat sb;
	char		*abs_path;
	int			ret;

	ret = 0;
	if (path)
		abs_path = ft_strjoin_infinite(3, path, "/", lex);
	else
		abs_path = ft_strdup(lex);
	if (stat(abs_path, &sb) == 0 &&
		(sb.st_mode & S_IXOTH) && !S_ISDIR(sb.st_mode))
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
	DIR				*dir;
	struct dirent	*info;
	char			**all_path;
	int				i;

	all_path = comp_get_all_path(edit);
	i = -1;
	while (all_path && all_path[++i])
	{
		if ((dir = opendir(all_path[i])))
		{
			while (dir && (info = readdir(dir)))
			{
				if (comp_is_pot_cmd(info->d_name, comp->str, all_path[i]))
					add_to_list(comp, info->d_name);
			}
			closedir(dir);
		}
	}
	ft_freetab(all_path);
	comp_add_pot_builtin(comp);
	comp_add_pot_words(comp);
}
