/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:57:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/09 14:17:23 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static int	edit_end(char **line, t_edit *edit)
{
	*edit->current = moove_last(*edit->current, &edit->curseur);
	*edit->current = push_new(*edit->current, '\n', &edit->curseur);
	handle_history_ret(*edit->current, edit->histo);
	*line = line_to_str(*edit->current);
	free_dblist(*edit->current);
	return (1);
}

int			edit_line(char **line, t_edit *edit)
{
	char	c;

	c = 0;
	while (reset_completion(c, edit->comp) && read(STDIN_FILENO, &c, 1))
	{
		if (c == 4 && !(*edit->current)->next && !(*edit->current)->prev
				&& !g_quote)
			return (0);
		else if (c == '\n')
			return (edit_end(line, edit));
		else if (c == 14)
			*edit->current = hist_down(*edit->current, edit->histo,
					edit->prompt_len, &edit->curseur);
		else if (c == 16)
			*edit->current = hist_up(*edit->current, edit->histo,
					edit->prompt_len, &edit->curseur);
		else if (c == 27)
			*edit->current = ft_line_esc(*edit->current, edit->prompt_len,
					&edit->curseur, edit->histo);
		else
			*edit->current = ft_line_usual(edit, c);
	}
	return (0);
}

int			ft_line_edition(char **line, int prompt_len, t_hist **histo,
			t_env *env)
{
	t_edit			edit;
	t_line			*current;
	t_curs			curseur;
	int				ret;

	if (prompt_len == -1 && ft_printf_fd(STDERR_FILENO, "{tred}> {eoc}"))
		prompt_len = 2;
	edit.prompt_len = prompt_len;
	current = create_elem(0, prompt_len + 1);
	init_hist(histo);
	init_curs(&curseur, prompt_len);
	edit.current = &current;
	edit.histo = histo;
	edit.curseur = curseur;
	edit.comp = init_t_comp();
	edit.env = env;
	g_ed = &edit;
	ret = edit_line(line, &edit);
	ft_clean_edit(&edit);
	return (ret);
}
