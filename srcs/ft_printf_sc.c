/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_sc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clauren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 21:27:22 by clauren           #+#    #+#             */
/*   Updated: 2020/07/25 17:00:24 by clauren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void				print_filler(char c, int n)
{
	while (n--)
		ft_putchar(c);
}

static	int			print_c(t_params *params, va_list *ap)
{
	char	c;
	int		n;
	char	f;

	f = ((params->flags & FL_ZERO) && !(params->flags & FL_MINUS)) ? '0' : ' ';
	n = 0;
	c = (params->type == '%') ? '%' : va_arg(*ap, int);
	if (params->width >= 0)
	{
		if (params->flags & FL_MINUS)
		{
			ft_putchar(c);
			while (++n < params->width)
				ft_putchar(f);
		}
		else
		{
			while (++n < params->width)
				ft_putchar(f);
			ft_putchar(c);
		}
	}
	return (n);
}

static	int			print_s(t_params *params, va_list *ap)
{
	char	*p;
	int		str_len;
	int		filler_len;
	char	f;
	int		i;

	i = 0;
	f = ((params->flags & FL_ZERO) && !(params->flags & FL_MINUS)) ? '0' : ' ';
	if (params->precision == -1 || params->precision < 0)
		params->precision = 0x7fffffff;
	p = va_arg(*ap, char *);
	if (p == (char *)0)
		p = "(null)";
	str_len = (ft_strlen(p) > params->precision)
			? params->precision : ft_strlen(p);
	filler_len = (params->width - str_len <= 0) ? 0 : params->width - str_len;
	if (params->width > 0 && (!(params->flags & FL_MINUS)))
		print_filler(f, filler_len);
	while (i < str_len)
		ft_putchar(p[i++]);
	if (str_len < params->width && (params->flags & FL_MINUS))
		print_filler(f, filler_len);
	return (str_len + filler_len);
}

int					print(t_params *params, va_list *ap)
{
	if (params->precision == 0)
		params->flags |= FL_Z_BLOCK;
	if (params->type == 'c' || params->type == '%')
		return (print_c(params, ap));
	if (params->type == 's')
		return (print_s(params, ap));
	if (params->type == 'd' || params->type == 'i')
		return (print_d(params, ap));
	if (params->type == 'p')
		return (print_uxp(params, ap, 1, 16));
	if (params->type == 'x')
		return (print_uxp(params, ap, 1, 16));
	if (params->type == 'X')
		return (print_uxp(params, ap, 0, 16));
	if (params->type == 'u')
		return (print_uxp(params, ap, 0, 10));
	return (0);
}
