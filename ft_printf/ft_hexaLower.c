/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexaLower.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:35:22 by woumecht          #+#    #+#             */
/*   Updated: 2022/11/08 14:56:13 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexalower(size_t n)
{
	int		cpp;
	char	*arr;

	cpp = 0;
	arr = "0123456789abcdef";
	if (n >= 16)
	{
		cpp += ft_hexalower(n / 16);
	}
	ft_putchar(arr[n % 16]);
	cpp++;
	return (cpp);
}
