/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:57:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/02 14:41:23 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		is_command(t_token token)
{
	(void)token;
	return (1);
}

int		is_semi_colon(char *str)
{
	(void)str;
	return (1);
}

t_cmd	*split_by_cmd(t_lex *lex)
{
	t_cmd *cmd;
	t_cmd *new;
	t_lex *tmp;

	cmd = NULL;
	tmp = lex;
	while (tmp)
	{
		if (is_command(tmp->token) == 1)
		{
			new = init_cmd();
			tmp = fill_cmd(new, tmp);
			cmd = cmd_push_back(cmd, new);
		}
		tmp = tmp->next;
	}
	return (cmd);
}

/*
**	On transforme [cmd1] -> [cmd2] -> [cmd3] -> [cmd1] -> [cmd2] -> [cmd3] -> [cmd4] -> [cmd1] -> [cmd2] ->  
**	en 	[cmd1] -> [cmd2] -> [cmd3] -> NULL
**		  |
**		[cmd1] -> [cmd2] -> [cmd3] -> [cmd4] -> NULL
**		  |
**		[cmd1] -> [cmd2] -> [cmd3] -> NULL
*/

void	split_by_semicolon(t_cmd *cmd)
{
	t_cmd *tmp;
	t_cmd *first;

	tmp = cmd;
	first = cmd;
	while (tmp)
	{
		if (is_semi_colon(tmp->separ) == 1)
		{
			first->next_semi = tmp->next;
			tmp->next = NULL;
			tmp = first->next_semi;
			first = tmp;
		}
		else
			tmp = tmp->next;
	}

}

/*
**	Tu m'envois la premiere node de la list de lex
*/

int		init_exec(t_lex *lex)
{
	t_cmd	*cmd;
	t_cmd	*tmp;
	int		ret;

	if (lex == NULL)
		return (-1);

// On transforme lex en liste chaine de t_cmd remplie
	cmd = split_by_cmd(lex);

// On separe les phrases simples (séparées par ';')
	split_by_semicolon(cmd);

// On lance l'exec phrases simple par phrases simple
	tmp = cmd;
	while (tmp)
	{
		ret = 0; // ret = do_exec(tmp);
		tmp = tmp->next;
	}
	ft_clean_cmd(cmd);
	return (ret);
}
