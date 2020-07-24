/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clauren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 21:07:10 by clauren           #+#    #+#             */
/*   Updated: 2020/07/23 23:05:42 by clauren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int			ft_strlen(char *s)
{
	size_t len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int			is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int			is_type(char c)
{
	char *types;

	types = "cspdiuxX%";
	while (*types)
		if (*types++ == c)
			return (1);
	return (0);
}

int			ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

void		ft_putstr(char *p)
{
	while (*p)
		ft_putchar(*p++);
}
