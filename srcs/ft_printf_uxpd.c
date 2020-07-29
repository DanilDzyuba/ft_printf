/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uxpd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clauren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 21:17:10 by clauren           #+#    #+#             */
/*   Updated: 2020/07/27 13:27:25 by clauren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static	void		print_d_f(t_params *params, t_lens *lens, int neg, char *p)
{
	if (neg && lens->f == '0')
		ft_putchar('-');
	else if (!neg && (params->flags & FL_PLUS))
	{
		lens->filler_len > 0 ? lens->filler_len-- : 1;
		if (lens->f == '0')
			ft_putchar('+');
	}
	else if (!neg && params->flags & FL_SPACE && ft_putchar(' '))
		lens->filler_len > 0 ? lens->filler_len-- : 1;
	if (params->width > 0 && (!(params->flags & FL_MINUS)))
		print_filler(lens->f, lens->filler_len);
	if (neg && lens->f == ' ')
		ft_putchar('-');
	else if (!neg && (params->flags & FL_PLUS) && lens->f == ' ')
		ft_putchar('+');
	if (lens->str_len < params->precision)
		print_filler('0', lens->zero_len);
	ft_putstr(p);
	if (lens->str_len < params->width && (params->flags & FL_MINUS))
		print_filler(lens->f, lens->filler_len);
}

static	int			print_d_h(t_params *params, char *p, int neg)
{
	t_lens lens;

	lens.f = (params->flags & FL_ZERO && params->precision <= 0
			&& !(params->flags & FL_Z_BLOCK)) ? '0' : ' ';
	lens.str_len = ft_strlen(p);
	lens.zero_len = (params->precision - lens.str_len > 0)
			? params->precision - lens.str_len : 0;
	lens.filler_len = (params->width > (lens.str_len + lens.zero_len))
			? params->width - lens.str_len - lens.zero_len - neg : 0;
	print_d_f(params, &lens, neg, p);
	if (!neg && ((params->flags & FL_PLUS) || (params->flags & FL_SPACE)))
		lens.filler_len++;
	if (neg)
		free(--p);
	else
		free(p);
	return (lens.zero_len + lens.filler_len + lens.str_len + neg);
}

int					print_d(t_params *params, va_list *ap)
{
	char		*p;
	int			neg;

	p = ft_ltoa_base(va_arg(*ap, int), 10, 0);
	if (!p)
		return (-1);
	neg = 0;
	if (*p == '-' && (neg = 1))
		p++;
	else if (*p == '0' && params->precision == 0)
		*p = '\0';
	return (print_d_h(params, p, neg));
}

static	int			print_uxp_h(t_params *params, char *p, char f, char pref)
{
	t_lens lens;

	lens.str_len = ft_strlen(p);
	lens.zero_len = (params->precision - lens.str_len > 0)
			? params->precision - lens.str_len : 0;
	if (pref)
		lens.str_len += 2;
	lens.filler_len = (params->width > (lens.str_len + lens.zero_len))
			? params->width - lens.str_len - lens.zero_len : 0;
	if (f == '0' && pref && ft_putchar('0'))
		ft_putchar(pref);
	if (params->width > 0 && (!(params->flags & FL_MINUS)))
		print_filler(f, lens.filler_len);
	if (f == ' ' && pref && ft_putchar('0'))
		ft_putchar(pref);
	if (lens.str_len <= params->precision)
		print_filler('0', lens.zero_len);
	ft_putstr(p);
	if (lens.str_len < params->width && (params->flags & FL_MINUS))
		print_filler(f, lens.filler_len);
	free(p);
	return (lens.str_len + lens.filler_len + lens.zero_len);
}

int					print_uxp(t_params *params, va_list *ap, int low, int base)
{
	char	*p;
	char	f;
	char	pref;

	f = (params->flags & FL_ZERO && params->precision <= 0
				&& !(params->flags & FL_Z_BLOCK)) ? '0' : ' ';
	pref = (char)NULL;
	if (params->type == 'p' && (pref = 'x'))
		p = ft_ltoa_base(va_arg(*ap, unsigned long), base, low);
	else
		p = ft_ltoa_base(va_arg(*ap, unsigned), base, low);
	if (!p)
		return (-1);
	if (params->flags & FL_HASH && (*p != '0'))
	{
		if (params->type == 'x' || params->type == 'X')
			pref = params->type;
	}
	if (*p == '0' && params->precision == 0)
		*p = '\0';
	return (print_uxp_h(params, p, f, pref));
}
