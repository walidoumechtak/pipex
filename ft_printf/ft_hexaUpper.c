/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexaUpper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:02:54 by woumecht          #+#    #+#             */
/*   Updated: 2022/11/05 08:18:33 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexaupper(unsigned int n)
{
	char	*arr;
	int		cpp;

	cpp = 0;
	arr = "0123456789ABCDEF";
	if (n >= 16)
		cpp += ft_hexaupper(n / 16);
	ft_putchar(arr[n % 16]);
	cpp++;
	return (cpp);
}
