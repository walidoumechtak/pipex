/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:34:34 by woumecht          #+#    #+#             */
/*   Updated: 2022/11/05 08:15:24 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	int		cpp;

	cpp = 0;
	if (n == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		cpp += 2;
		n = 147483648;
	}
	else if (n < 0)
	{
		ft_putchar('-');
		cpp++;
		n *= -1;
	}
	if (n >= 10)
		cpp += ft_putnbr(n / 10);
	ft_putchar((n % 10) + 48);
	cpp++;
	return (cpp);
}
