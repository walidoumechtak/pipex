/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:34:54 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/27 07:53:50 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_perror_fork(t_pipe *ptr)
{
	free(ptr);
	perror("Failed to create a proccess");
}

void	ft_perror_open(t_pipe *ptr)
{
	free(ptr);
	ft_printf("%s\n", strerror(errno));
}

void	ft_perror_pipe(t_pipe *ptr)
{
	free(ptr);
	perror("failded to Create a pipe");
}
