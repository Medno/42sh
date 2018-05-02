/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vlocal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 11:22:11 by hlely             #+#    #+#             */
/*   Updated: 2018/05/02 12:15:07 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VLOCAL_H
# define VLOCAL_H

# include "sh.h"

# define NOPRINT	0
# define PRINT		1
# define NOINC		0
# define INC		1
# define NOCLEAN	0
# define CLEAN		1
# define NOERR		0
# define ERR		1
# define BOTH		0
# define ENV		1
# define LOC		2
# define TOLOC		0
# define TOENV		1

int		clean_arg(char ***arg);
int		equ_index(char *str, char c);
int		is_valid_identifier(char *function, char *arg, int print);
int		is_all_valid_identifier(char *function, char *arg, int print);
int		ft_export(t_init *init, char ***entry);
int		check_local(char ***arg, int clean);
int		is_in_env(t_env *env, char *name);
int		ft_set_local(t_env **loc, t_env **env, char **arg);
int		ft_set(t_env *loc, t_env *env, char **entry);
int		ft_unset(t_env **loc, t_env **env, char **arg);
int		export_equal(t_init *init, char *arg, int whereto);
int		switch_env_to_loc(t_init *init, char **arg);
int		switch_loc_to_env(t_init *init, char **arg);

void	ft_set_variable(t_env **loc, t_env **env, char *arg, int where);

int		inc_opt(char **arg);
int		export_usage(void);
int		not_an_identifier(char *function, char *arg);
int		read_only_error(char *arg, int free);
#endif
