/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:22:35 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/19 09:05:41 by woumecht         ###   ########.fr       */
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

char    *remove_equal_from_path(char *str)
{
    char    **arr;
    char    *res;
    
    arr = ft_split(str, '=');
    res = ft_strjoin(res, arr[1]);
    free_all(arr);
    return (res);
}

char    **get_cmd_from_input(char *str)
{
    char    **arr;
    char *
    arr = ft_split(str, ' ');
    return (arr);
}

char *path_cmd(char *str, char *cmd)
{
    int i;
    char **p;
    char *res;
    char *removed_equal;
    char *joined;

    removed_equal = remove_equal_from_path(str);
    p = ft_split(removed_equal, ':');
    i = 0;
    while (p[i])
    {
        joined = ft_strjoin(p[i], cmd);
        if (access(joined, F_OK) == 0)
        {
            res = joined;
            free_all(p);
            return (res);
        }
        i++;
    }
    free(removed_equal);
    return (free_all(p), NULL);
}

int main(int ac, char **av, char **env)
{
    t_pipe  *ptr;

    ptr->cmd1 = get_cmd_from_input(av[2]);
    ptr->cmd2 = get_cmd_from_input(av[3]);
    ptr->path_cmd1 = path_cmd(env[6], ptr->cmd1[0]);
    ptr->path_cmd1 = path_cmd(env[6], ptr->cmd2[0]);
    if (pipe(ptr->fd) < 0)
        return (1);
    ptr->stdout_copy = dup(1);
    if (ac == 5)
    {
        ptr->pid = fork();
        if (ptr->pid == 0)
        {
            ptr->fd_infile = open(av[1], O_RDONLY);
            if (ptr->fd_infile == -1)
                ft_perror();
            
            
        }
        else
        {
            ptr->fd_outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC);
        }
    }
    else
        printf("to many argements !\n");
}


