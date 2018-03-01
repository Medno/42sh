/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 13:27:35 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/01 14:02:12 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	is_redir(t_lex *tmp)
{
	if (ft_strequ(tmp->value, ">") || ft_strequ(tmp->value, "<") ||
			tmp->token == GREATAND || tmp->token == LESSAND ||
			tmp->token == DGREAT || tmp->token == DLESS ||
			tmp->token == CLOBBER || tmp->token == DLESSDASH ||
			tmp->token == LESSGREAT)
		return (1);
	return (0);
}

int	check_first(t_lex *first)
{
	if (first->token != WORD && !is_redir(first) && first->token != QUOTE)
	{
		if (first->token != EOI)
			ft_putendl("syntax error");
		del_lex(first);
		return (1);
	}
	return (0);
}

int	err_pars(t_lex *tmp, t_lex *del)
{
	if (is_redir(tmp))
	{
		if (tmp->next && tmp->next->token != WORD)
		{
			ft_putendl("syntax error");
			del_lex(del);
			return (1);
		}
	}
	if (tmp->next && (tmp->token == AND_IF || tmp->token == OR_IF ||
				ft_strequ(tmp->value, "|") || tmp->token == DLESSDASH))
		if (tmp->next->token != EOI && tmp->next->token != WORD &&
				tmp->next->token != QUOTE)
		{
			ft_putendl("syntax error");
			del_lex(del);
			return (1);
		}
	return (0);
}

int	repeat_line_edition(t_init *init, t_lex *tmp)
{
	char	*line_tmp;

	if ((tmp->token == QUOTE && g_quote) || 
			(tmp->next && tmp->next->token == EOI && (tmp->token == AND_IF
			  || tmp->token == OR_IF || ft_strequ(tmp->value, "|") ||
			  tmp->token == DLESSDASH)))
	{
		ft_cfmakeraw(&(init->current));
		ft_line_edition(&line_tmp, -1, &(init->historic), init->new_env);
		ft_cfmakedefault(&(init->current));
		if ((tmp->token == QUOTE && g_quote))
			init->str = ft_strjoindel(init->str, "\n");
		init->str = ft_strjoindel(init->str, line_tmp);
		del_lex(init->lex);
		ft_strdel(&line_tmp);
		return (1);
	}
	return (0);
}

int	parser(t_init *init)
{
	t_lex	*tmp;
	t_ast	*ast;

	print_lex(init->lex);
	if (check_first(init->lex))
		return (0);
	tmp = init->lex;
	while (tmp->token != EOI)
	{
		if (err_pars(tmp, init->lex))
			return (0);
		if (repeat_line_edition(init, tmp))
			return (1);
		tmp = tmp->next;
	}
	tmp = init->lex;
	ast = build_ast(tmp);
	print_ast(ast, NULL);
	del_ast(&ast);
	del_lex(init->lex);
	return (0);
}
/*
   int	parser(t_lex *first, t_hist **histo, char **line, struct termios cur)
   {
   t_lex	*tmp;
   t_ast	*ast;
   int		build;
   char	*line_tmp;

   print_lex(first);
   build = check_first(first);
   tmp = first;
   while (tmp->token != EOI && !build)
   {
   if (err_pars(tmp))
   {
   ft_putendl("syntax error");
   build = 1;
   }
   if ((tmp->token == QUOTE && g_quote) || 
   (tmp->next && tmp->next->token == EOI && (tmp->token == AND_IF
   || tmp->token == OR_IF || ft_strequ(tmp->value, "|"))))
   {
   ft_cfmakeraw(&cur);
   ft_line_edition(&line_tmp, -1, histo);
   ft_cfmakedefault(&cur);
   if ((tmp->token == QUOTE && g_quote))
 *line = ft_strjoindel(*line, "\n");
 *line = ft_strjoindel(*line, line_tmp);
 del_lex(first);
 return (1);
 }
 tmp = tmp->next;
 }
 if (!build)
 {
 tmp = first;
 ast = build_ast(tmp);
 print_ast(ast, NULL);
 del_ast(&ast);
 }
 del_lex(first);
 return (0);
 }*/
