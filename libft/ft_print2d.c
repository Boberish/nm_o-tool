/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaylor <jaylor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 09:10:04 by jaylor            #+#    #+#             */
/*   Updated: 2017/11/30 10:50:18 by jaylor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print2d(char **array)
{
	int i;
	int f;

	i = 0;
	f = 0;
	while (array[i])
	{
		f = 1;
		ft_putstr(array[i++]);
		ft_putchar('\n');
	}
	if (f == 0)
		return (-1);
	return (0);
}