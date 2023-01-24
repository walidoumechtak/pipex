/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:07:14 by woumecht          #+#    #+#             */
/*   Updated: 2022/11/08 14:56:06 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf(const char *s, ...);
int	ft_putchar(char c);
int	ft_vprintf(va_list ptr, int i, char *s);
int	ft_putstr(char *s);
int	ft_putnbr(int n);
int	ft_printuns(unsigned int n);
int	ft_hexalower(size_t n);
int	ft_hexaupper(unsigned int n);

#endif
