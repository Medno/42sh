/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:47:36 by hlely             #+#    #+#             */
/*   Updated: 2018/03/14 15:47:51 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_redir	*handle_double(t_redir *redir)
{
	int		fd;

	if (!redir->file)
		redir->file = ft_itoa(redir->fd_out);
	if ((fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
	{
		which_error(file_error(redir->file), redir->file);
		return (NULL);
	}
	dup2(fd, STDOUT_FILENO);
	redir->fd_out = fd;
	return (redir);
}
