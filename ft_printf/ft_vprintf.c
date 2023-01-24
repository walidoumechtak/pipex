/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:10:27 by woumecht          #+#    #+#             */
/*   Updated: 2022/11/08 14:56:32 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_vprintf(va_list ptr, int i, char *s)
{
	int	cpp;

	cpp = 0;
	if (s[i] == 'c')
		cpp = ft_putchar(va_arg(ptr, int));
	else if (s[i] == 's')
		cpp = ft_putstr(va_arg(ptr, char *));
	else if (s[i] == 'd' || s[i] == 'i')
		cpp = ft_putnbr(va_arg(ptr, int));
	else if (s[i] == '%')
		cpp = ft_putchar('%');
	else if (s[i] == 'u')
		cpp = ft_printuns(va_arg(ptr, unsigned int));
	else if (s[i] == 'x')
		cpp = ft_hexalower(va_arg(ptr, unsigned int));
	else if (s[i] == 'X')
		cpp = ft_hexaupper(va_arg(ptr, unsigned int));
	else if (s[i] == 'p')
	{
		write(1, "0x", 2);
		cpp = ft_hexalower(va_arg(ptr, size_t)) + 2;
	}
	else
		cpp = ft_putchar(s[i]);
	return (cpp);
}
