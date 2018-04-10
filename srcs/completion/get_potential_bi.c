/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_potential_bi.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 09:53:18 by hfouques          #+#    #+#             */
/*   Updated: 2018/04/10 09:53:19 by hfouques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static int	comp_is_pot_bi(char *lex, char *str)
{
	int		ret;

	ret = 0;
	if (str == NULL || ft_strlen(str) == 0)
		ret = 0;
	else if (ft_strncmp(lex, str, ft_strlen(str)) == 0)
		ret = 1;
	return (ret);
}

static char	**get_builtin_list(void)
{
	char **bi_list;

	bi_list = ft_memalloc(sizeof(char *) * 12);
	if (bi_list)
	{
		bi_list[0] = ft_strdup("cd");
		bi_list[1] = ft_strdup("export");
		bi_list[2] = ft_strdup("echo");
		bi_list[3] = ft_strdup("env");
		bi_list[4] = ft_strdup("setenv");
		bi_list[5] = ft_strdup("unsetenv");
		bi_list[6] = ft_strdup("export");
		bi_list[7] = ft_strdup("set");
		bi_list[8] = ft_strdup("unset");
		bi_list[9] = ft_strdup("exit");
		bi_list[10] = ft_strdup("history");
		bi_list[11] = NULL;
	}
	return (bi_list);
}

void		comp_add_pot_builtin(t_comp *comp)
{
	t_lcomp	*new;
	char	**builtin_list;
	int		i;

	builtin_list = get_builtin_list();
	i = 0;
	while (builtin_list[i])
	{
		if (comp_is_pot_bi(builtin_list[i], comp->str))
		{
			new = init_t_lcomp();
			new->cmd = ft_strdup(builtin_list[i]);
			comp->list = lcomp_push_back(comp->list, new);
		}
		i++;
	}
	ft_freetab(builtin_list);
}
