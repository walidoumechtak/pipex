/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:34:54 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/25 13:36:08 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_perror_fork(void)
{
	perror("Failed to create a proccess");
}

void	ft_perror_open(void)
{
	perror("Failed to open file");
}

void ft_perror_pipe(void)
{
	perror("failded to Create a pipe");
}