/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:22:35 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/18 10:56:30 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <string.h>
#include <stdlib.h>
 #include <sys/wait.h>
 

int main(int ac, char **av, char **env)
{
    int fd[2];
    int pid;
    int stdout_copy;
    char    
    stdout_copy = dup(1);
    if (ac == 5)
    {
        pid = fork();
        if (pid == 0)
        {
            
        }
        else
        {
            
        }
    }
    else
        printf("to many argements !\n");
}


