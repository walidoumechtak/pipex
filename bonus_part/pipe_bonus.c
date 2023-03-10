/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:21:25 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/27 11:45:14 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	init_struct_elem(t_pipe *ptr, int ac, char **av, char **env)
{
	ptr->cmd1 = get_cmd_from_input(av[3]);
	ptr->cmd2 = get_cmd_from_input(av[4]);
	ptr->path_cmd1 = path_cmd(ptr, env, ptr->cmd1[0]);
	ptr->path_cmd2 = path_cmd(ptr, env, ptr->cmd2[0]);
	ptr->fd_outfile = open(av[5], O_WRONLY | O_CREAT | O_APPEND, 0777);
	ptr->fd_temp_file = open("temp", O_WRONLY | O_CREAT, 0777);
	if ((ptr->fd_outfile < 0 || (ptr->fd_temp_file < 0)) && ac == 6)
		ft_perror_open(ptr);
	if (ptr->path_cmd2 == NULL && ac == 6)
	{
		ft_printf("commande not found : %s\n", ptr->cmd2[0]);
		if (ptr->path_cmd1 != NULL)
		{
			free(ptr);
			exit(127);
		}
	}
	if (ptr->path_cmd2 == NULL && ptr->path_cmd1 == NULL && ac == 5)
	{
		ft_printf("commande not found : %s", ptr->cmd1[0]);
		free(ptr);
		exit(127);
	}
}

void	read_here_doc(t_pipe *ptr, char **av)
{
	char	**arr;

	write(1, "pipe heredoc> ", 15);
	ptr->line = get_next_line(0);
	if (!ptr->line)
		return ;
	while (ptr->line)
	{
		arr = ft_split(ptr->line, '\n');
		if (ft_strcmp(arr[0], av[2]) == 0)
		{
			free_all(arr);
			break ;
		}
		free_all(arr);
		fd_put_string(ptr->line, ptr->fd_temp_file);
		free(ptr->line);
		write(1, "pipe heredoc> ", 15);
		ptr->line = get_next_line(0);
	}
	free(ptr->line);
}

void	here_doc(t_pipe *ptr, int ac, char **av, char **env)
{
	init_struct_elem(ptr, ac, av, env);
	if (access(av[5], X_OK) != 0)
	{
		ft_printf("permission denied: %s\n", av[5]);
		exit(0);
	}
	read_here_doc(ptr, av);
	close(ptr->fd_temp_file);
	ptr->fd_temp_file = open("temp", O_RDONLY);
	if (ptr->fd_temp_file < 0)
		ft_perror_open(ptr);
}

int	main(int ac, char **av, char **env)
{
	t_pipe	*ptr;

	if (ft_strcmp(av[1], "here_doc") == 0 && ac == 6)
	{
		ptr = malloc(sizeof(t_pipe));
		if (!ptr)
			exit(1);
		if (pipe(ptr->fd) < 0)
			ft_perror_pipe(ptr);
		here_doc(ptr, ac, av, env);
		cmd_bonus_1(ptr, env);
		cmd_bonus_2(ptr, env);
		close(ptr->fd[0]);
		close(ptr->fd[1]);
		while (wait(NULL) != -1)
			;
		free(ptr);
	}
}
