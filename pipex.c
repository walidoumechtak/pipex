/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:22:35 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/18 14:38:45 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    ft_perror()
{
    perror("Failed to open file");
    exit (0);
}

void    free_all(char **s)
{
    int i;
    
    i = 0;
    while (s[i])
    {
        free(s[i]);
        i++;
    }
    free(s);
}

char *path_cmd(char *str, char *cmd)
{
    int i;
    char **p;
    char *r;

    p = ft_split(str, ':');
    i = 0;
    while (p[i])
    {
        if (access(p[i], F_OK) == 0)
        {
            r = p[i];
            free_all(p);
            return (r);
        }
        i++;
    }
    if (access(p[0], F_OK) == 0)
    {
        r =   p[i];
        free_all(p);
        return (r);  
    }
    free_all(p);
    return (NULL);
}

int main(int ac, char **av, char **env)
{
    int fd[2];
    int fd_outfile;
    int fd_infile;
    int pid;
    int stdout_copy;
    char **cmd1;

    cmd1 = cmd1(av[2], env);
    if (!path)
        ft_perror();
    if (pipe(fd) < 0)
        return (1);
    stdout_copy = dup(1);
    if (ac == 5)
    {
        pid = fork();
        if (pid == 0)
        {
            fd_infile = open(av[1], O_RDONLY);
            if (fd_infile == -1)
                ft_perror();
            
            
        }
        else
        {
            fd_outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC);
        }
    }
    else
        printf("to many argements !\n");
}


