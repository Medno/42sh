/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:24:09 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/06 12:32:00 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
/*
**
** Ceci est une ebauche de l'execution. Nous pouvons commencer a travailler
** sur des nouveaux builtins. Good luck >)
**
*/
int		check_builtins(char **entry, t_init *init)
{
	int		check;

	check = 0;
	if (ft_strequ("cd", *entry) && (check = 1)) // CUI LA ET TOU BON
		ft_cd(&init->new_env, entry, ft_tablen(entry));
	else if (ft_strequ("echo", *entry) && (check = 1)) // A MODIFIER (NO GESTION DAFFICHAGE DE VARIABLE >> LEXER?PARSER
		ft_echo(&init->new_env, &entry[1]);
	else if (ft_strequ("env", *entry) && (check = 1)) // A FINIR / MODIFIER
		ft_env(init->new_env, entry);
	else if (ft_strequ("setenv", *entry) && (check = 1)) // A MODIFIER OU VIRER A VOIR
		ft_setenv(&init->new_env, entry[1], entry[2]);
	else if (ft_strequ("unsetenv", *entry) && (check = 1))  // A RECHECK
		ft_unsetenv(&init->new_env, entry[1]);
	else if (ft_strequ("export", *entry) && (check = 1)) // A FAIRE
		;
	else if (ft_strequ("history", *entry) && (check = 1)) // JMEN OCCUPE (kiyan)
		ft_history(&init->historic, entry, ft_tablen(entry));
	return (check);
}

int		check_cmd(t_cmd *cmd, t_init *init)
{
	if (check_builtins(cmd->arg, init))
		return (1);
	else
		return (0);
}

int		exec_start(t_init *init)
{
	t_cmd	*tmp;
	t_cmd	*tmp2;
	int		std_fd[3];

	tmp2 = init->cmd;
	while (tmp2)
	{
		tmp = tmp2;
		while (tmp)
		{
			saving_fd(std_fd);
			if (!redirection(tmp))
				return (2);
			check_cmd(tmp, init);
			tmp = tmp->next;
			reset_fd(std_fd);
		}
		tmp2 = tmp2->next_semi;
	}
	return (1);
}
