/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:17:02 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/18 14:12:19 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char *ft_strcat(char *s1, char *s2)
{
    char *cat;
    int len1;
    int len2;
    int i;

    i = 0;
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    cat = malloc(len1 + len2 + 1);    
    
    while (s1[i])
    {
        cat[i] = s1[i];
        i++;
    }
    i = 0;
    while (s2[i])
    {
        cat[len1] = s2[i];
        i++;
        len1++;
    }
    cat[len1] = '\0';
    return (cat);
}
