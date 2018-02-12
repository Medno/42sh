/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:50:19 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/12 08:56:55 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include "libft.h"
# define BUFF_SIZE 100

typedef struct	s_sort
{
	int		fd;
	char	stock[BUFF_SIZE + 1];
}				t_sort;

int				get_next_line(const int fd, char **line);

#endif
