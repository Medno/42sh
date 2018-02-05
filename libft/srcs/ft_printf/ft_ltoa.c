/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 09:17:08 by kyazdani          #+#    #+#             */
/*   Updated: 2017/12/13 11:17:19 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_ltoa(long long n, int apo)
{
	if (n >= 0)
		return (ft_untoa(n, apo));
	else
		return (ft_strjoin("-", ft_untoa(-n, apo)));
}
