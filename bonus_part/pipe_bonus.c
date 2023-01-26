/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:21:25 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/26 06:55:48 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	read_here_doc(t_pipe *ptr, char **av, int ac)
{
	char	**arr;
	
	(void)ac;
	ptr->fd_temp_file = open("temp", O_WRONLY | O_CREAT, 0777);
	write(1, "pipe heredoc> ", 15);
	ptr->line = get_next_line(0);
	if (!ptr->line)
		return ;
	while (ptr->line)
	{
		arr = ft_split(ptr->line, '\n');
		if (ft_strcmp(arr[0], av[2]) == 0)
			break ;
		free_all(arr);
		fd_put_string(ptr->line, ptr->fd_infile);
		free(ptr->line);
		write(1, "pipe heredoc> ", 15);
		ptr->line = get_next_line(0);
	}
	free(ptr->line);
}

void	here_doc(t_pipe *ptr, int ac, char **av, char **env)
{
	ptr->bonus_int = 1; // to indicate if we can use unlink or not
	init_struct_elem(ptr, ac, av, env);
	if (pipe(ptr->fd) < 0)
		return ;
	read_here_doc(ptr, av, ac);
	close(ptr->fd_temp_file);
	ptr->fd_temp_file = open("temp", O_RDONLY);
	if (ptr->fd_temp_file < 0)
		ft_perror_open();
	cmd1(ptr, env);
	cmd2(ptr, env);
	while (wait(NULL) != -1)
		;
}

int	main(int ac, char **av, char **env)
{
	t_pipe *ptr;

	ptr = malloc(sizeof(t_pipe));
	if (!ptr)
		return (1);
	if (ft_strcmp(av[1], "here_doc") == 0 && ac == 6)
		here_doc(ptr, ac, av, env);
	free(ptr);
}
