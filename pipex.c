/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:22:35 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/19 20:20:03 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_perror(void)
{
	perror("Failed to open file");
	exit(0);
}

void	free_all(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

char	*remove_equal_from_path(char *str)
{
	char	**arr;
	char	*res;

	res = NULL;
	arr = ft_split(str, '=');
	res = ft_strjoin(res, arr[1]);
	free_all(arr);
	return (res);
}

char	**get_cmd_from_input(char *str)
{
	char	**arr;

	arr = ft_split(str, ' ');
	return (arr);
}

char	*path_cmd(char *str, char *cmd)
{
	int		i;
	char	**p;
	char	*res;
	char	*removed_equal;
	char	*joined;
	char	*temp;

	removed_equal = remove_equal_from_path(str);
	p = ft_split(removed_equal, ':');
	i = 0;
	while (p[i])
	{
		temp = ft_strjoin(p[i], "/");
		joined = ft_strjoin(temp, cmd);
		free(temp);
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

void	init_struct_elem(t_pipe *ptr, int ac, char **av, char **env)
{
	ptr->cmd1 = get_cmd_from_input(av[2]);
	ptr->cmd2 = get_cmd_from_input(av[3]);
	ptr->path_cmd1 = path_cmd(env[6], ptr->cmd1[0]);
	ptr->path_cmd2 = path_cmd(env[6], ptr->cmd2[0]);
	ptr->fd_outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	ptr->fd_infile = open(av[1], O_RDONLY);
	if (ptr->fd_infile == -1 && ac == 5)
		ft_perror();
	if (ptr->path_cmd2 == NULL && ac == 5)
		perror("command not found");
}

void	dup_and_execev(t_pipe *ptr, int n, char **env)
{
	if (n == 1)
	{
		close(ptr->fd[0]);
		dup2(ptr->fd_infile, 0);
		dup2(ptr->fd[1], 1);
		execve(ptr->path_cmd1, ptr->cmd1, env);
		close(ptr->fd[1]);
	}
	else
	{
		close(ptr->fd[1]);
		dup2(ptr->fd[0], 0);
		dup2(ptr->fd_outfile, 1);
		execve(ptr->path_cmd2, ptr->cmd2, env);
		close(ptr->fd[0]);
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipe	*ptr;

	ptr = malloc(sizeof(t_pipe));
	if (!ptr)
		return (1);
	init_struct_elem(ptr, ac, av, env);
	if (pipe(ptr->fd) < 0)
		return (1);
	ptr->stdout_copy = dup(1);
	ptr->stdin_copy = dup(0);
	if (ac == 5)
	{
		pipe(ptr->fd);
		ptr->pid = fork();
		if (ptr->pid == 0)
		{
			dup_and_execev(ptr, 1, env);
		}
		else
		{
			dup_and_execev(ptr, 2, env);
		}
		while (wait(NULL) != -1)
			;
	}
	else
		write(2, "to many argements !\n", 20);
	free(ptr);
}
