/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_put_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 06:42:19 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/23 06:44:32 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void    fd_put_char(char c, int fd)
{
    write(fd, &c, 1);
}

void    fd_put_string(char *s, int fd)
{
    int i;

    i = 0;
    while (s[i])
    {
        fd_put_char(s[i], fd);
        i++;
    }
}