/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnienow <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:39:28 by mnienow           #+#    #+#             */
/*   Updated: 2019/03/15 13:39:32 by mnienow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int        ft_iswhitespace(char const c)
{
    if (c == ' ' || c == '\n' || c == '\t' || c == '\v'
        || c == '\r' || c == '\f')
        return (1);
    return (0);
}

int    base(int c, int base)
{
    char *str = "0123456789abcdefx";
    char *str2 = "0123456789ABCDEFX";
    int  i = 0;

    while (i < base)
    {
        if (c == str[16] || c == str2[16])
            return (0);
        if (c == str[i] || c == str2[i])
            return (i);
        i++;
    }
    return (-1);
}

int ft_atoi_base(const char *str, int str_base)
{
    int nb = 0;
    int negatif = 0;
    int    i = 0;
    while (ft_iswhitespace(str[i]))
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            negatif = 1;
        i++;
    }
    while (base(str[i], str_base) != -1)
    {
        nb = nb * str_base;
        nb = nb + base(str[i], str_base);
        i++;
    }
    if (negatif)
        return (-nb);
    return (nb);
}