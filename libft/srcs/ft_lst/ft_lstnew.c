/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:54:36 by kyazdani          #+#    #+#             */
/*   Updated: 2017/11/11 15:48:50 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	if ((list = malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (!content)
	{
		list->content_size = 0;
		list->content = NULL;
		list->next = NULL;
	}
	else
	{
		if ((list->content = malloc(content_size)) == NULL)
			return (NULL);
		list->content = ft_memcpy(list->content, content, content_size);
		list->content_size = content_size;
		list->next = NULL;
	}
	return (list);
}
