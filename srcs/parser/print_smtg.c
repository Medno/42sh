/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_smtg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:54:26 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/09 14:33:43 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_ast(t_ast *root, char *pos)
{
	if (root)
	{
		if (pos)
			ft_putendl(pos);
		if (!root->parent)
			ft_putendl("Racine");
		else
		{
			ft_putstr("Fils de : ");
			ft_putendl(root->parent->value);
		}
		if (root->cmd)
			print_cmd(root->cmd);
		else if (root->value)
			ft_putendl(root->value);
		if (root->left)
			print_ast(root->left, "Fils Gauche");
		if (root->right)
			print_ast(root->right, "Fils Droit");
	}
}

void	print_redir(t_cmd *tmp_2)
{
	t_redir	*leak;

	leak = tmp_2->redir;
	while (leak)
	{
		ft_printf("fd_in : |%d|\ntoken : |%s|\nfd_out : ",
				leak->fd_in, leak->token);
		if (leak->file)
			ft_putstr(leak->file);
		else
			ft_putnbr(leak->fd_out);
		ft_putchar('\n');
		leak = leak->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;
	t_cmd	*tmp_2;

	tmp = cmd;
	while (tmp)
	{
		ft_printf("Nouvelle commande :\n");
		tmp_2 = tmp;
		while (tmp_2)
		{
			i = 0;
			if (tmp_2->arg)
				while (tmp_2->arg[i])
				{
					ft_printf("Parametre %d : |%s|\n", i, tmp_2->arg[i]);
					i++;
				}
			if (tmp_2->separ)
				ft_printf("Separateur : |%s|\n", tmp_2->separ);
			print_redir(tmp_2);
			tmp_2 = tmp_2->next;
		}
		tmp = tmp->next_semi;
	}
}
