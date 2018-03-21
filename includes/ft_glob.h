/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 15:01:58 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/21 15:48:28 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GLOB_H
# define FT_GLOB_H

# include "sh.h"

char		*ft_glob(char *init);
t_glpath	*parse_glob(char *str, int len);
int			check_glob(char *str);
void		expand_list(t_glpath **list);

#endif
