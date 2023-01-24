/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printUns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 22:16:33 by woumecht          #+#    #+#             */
/*   Updated: 2022/11/08 13:21:26 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printuns(unsigned int n)
{
	int		cpp;

	cpp = 0;
	if (n >= 10)
		cpp += ft_printuns(n / 10);
	ft_putchar((n % 10) + 48);
	cpp++;
	return (cpp);
}
