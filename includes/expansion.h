/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:24:33 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/21 18:51:55 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "sh.h"

/*
** expansions
*/
char	*exp_tilde(t_init *init, char *str, int len);
char	*dollar_exp(t_init *init, char *str, char ***tab, int *index);
char	*dollar_modify_str(t_init *init, char *str, int *replace, int *i);
char	*err_dollar(t_init *init, char *str);
char	**addtab_index(char **tab, char **add, int i);
char	*return_newtab(char *res, char ***tab, int *index);
int		only_space(char *str);
/*
** quote removal
*/
int		is_quote_bslash(char c);
void	put_in_buffer(char buffer[], char c);
void	word_exp(t_init *init, t_ast *ast);
char	*delete_esc(char *str, int len);
char	*esc_backslash(char *str, int *i);
char	*esc_simple_qu(char *str, int *i, int len);
char	*esc_double_qu(char *str, int *i, int len);
void	ast_expansion(t_init *init, t_ast *ast);

#endif
