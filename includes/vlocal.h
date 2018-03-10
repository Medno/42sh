/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 17:36:55 by hlely             #+#    #+#             */
/*   Updated: 2018/03/10 17:39:06 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VLOCAL_H
# define VLOCAL_H

# include "sh.h"

int		ft_export(t_env **loc_env, t_env **new_env, char **arg);
int		check_local(char **arg);
int		ft_set_local(t_env **lc, char **arg);

#endif
