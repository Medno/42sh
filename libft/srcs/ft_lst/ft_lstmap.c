/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:18:48 by kyazdani          #+#    #+#             */
/*   Updated: 2017/11/09 21:31:10 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*tmp;

	new = NULL;
	tmp = NULL;
	while (lst != NULL)
	{
		if (new == NULL)
		{
			new = f(lst);
			tmp = new;
		}
		else
		{
			new->next = f(lst);
			new = new->next;
		}
		lst = lst->next;
	}
	return (tmp);
}
