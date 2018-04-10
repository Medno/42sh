/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_potential_words.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 10:01:51 by hfouques          #+#    #+#             */
/*   Updated: 2018/04/10 10:01:53 by hfouques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static int	comp_is_pot_words(char *lex, char *str)
{
	int		ret;

	ret = 0;
	if (str == NULL || ft_strlen(str) == 0)
		ret = 0;
	else if (ft_strncmp(lex, str, ft_strlen(str)) == 0)
		ret = 1;
	return (ret);
}

static char	**get_word_list(void)
{
	char **word_list;

	word_list = ft_memalloc(sizeof(char *) * 14);
	if (word_list)
	{
		word_list[0] = ft_strdup("if");
		word_list[1] = ft_strdup("then");
		word_list[2] = ft_strdup("else");
		word_list[3] = ft_strdup("elif");
		word_list[4] = ft_strdup("fi");
		word_list[5] = ft_strdup("do");
		word_list[6] = ft_strdup("done");
		word_list[7] = ft_strdup("case");
		word_list[8] = ft_strdup("esac");
		word_list[9] = ft_strdup("while");
		word_list[10] = ft_strdup("until");
		word_list[11] = ft_strdup("for");
		word_list[12] = ft_strdup("in");
		word_list[13] = NULL;
	}
	return (word_list);
}

void		comp_add_pot_words(t_comp *comp)
{
	t_lcomp	*new;
	char	**word_list;
	int		i;

	word_list = get_word_list();
	i = 0;
	while (word_list[i])
	{
		if (comp_is_pot_words(word_list[i], comp->str))
		{
			new = init_t_lcomp();
			new->cmd = ft_strdup(word_list[i]);
			comp->list = lcomp_push_back(comp->list, new);
		}
		i++;
	}
	ft_freetab(word_list);
}
