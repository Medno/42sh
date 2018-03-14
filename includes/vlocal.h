/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vlocal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 11:22:11 by hlely             #+#    #+#             */
/*   Updated: 2018/03/14 15:41:02 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VLOCAL_H
# define VLOCAL_H

# include "sh.h"

# define NOPRINT	0
# define PRINT		1
# define NOCLEAN	0
# define CLEAN		1
# define BOTH		0
# define ENV		1
# define LOC		2

int		is_valid_identifier(char *arg, int print);
int		ft_export(t_init *init, char ***entry);
// int		ft_export(t_env **loc_env, t_env **new_env, char **arg);
int		check_local(char ***arg, int clean);
int		is_in_env(t_env *env, char *name);
int		ft_set_local(t_env **loc, t_env **env, char **arg);
int		ft_set(t_init *init, char ***entry);
int		ft_unset(t_init *init, char ***entry);
// int		ft_set(t_env *loc_env, t_env *new_env, char **arg);
// int		ft_unset(t_env **loc, t_env **env, char **arg);

void	ft_set_variable(t_env **loc, t_env **env, char *arg, int where);

#endif
