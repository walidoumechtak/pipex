/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:22:35 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/15 18:06:16 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
 #include <sys/wait.h>

int main(int ac, char **av)
{
    ac += 0;
    (void) av;
    int id = fork();

    if (id == 0)
    {
        printf("--- pid : %d, id fork : %d \n", getpid(), id);
    }
    else
        printf("pid : %d, id fork : %d \n", getpid(), id);
}