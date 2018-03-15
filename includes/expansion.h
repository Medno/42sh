/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:24:33 by pchadeni          #+#    #+#             */
/*   Updated: 2018/03/15 17:29:58 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "sh.h"

/*
** expansions
*/
t_cmd	*begin_expansion(t_init *init, t_cmd *cmd);
char	*exp_tilde(t_init *init, char *str, int len);
char	*dollar_exp(t_init *init, char *str);
/*
** quote removal
*/
int		is_quote_bslash(char c);
void	put_in_buffer(char buffer[], char c);
void	word_exp(t_init *init, t_ast *ast);
char	*delete_esc(t_init *init, char *str, int len);
char	*esc_backslash(char *str, int *i);
char	*esc_simple_qu(char *str, int *i, int len);
char	*esc_double_qu(t_init *init, char *str, int *i, int len);

#endif
