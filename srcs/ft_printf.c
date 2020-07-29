/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clauren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 21:30:56 by clauren           #+#    #+#             */
/*   Updated: 2020/07/27 14:09:13 by clauren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static	void		p_flags(char **fmt, t_params *params)
{
	while (1)
	{
		if (**fmt == '-')
		{
			params->flags |= FL_MINUS;
			params->flags &= (~FL_ZERO);
		}
		else if (**fmt == '0')
		{
			if (!(params->flags & FL_MINUS))
				params->flags |= FL_ZERO;
		}
		else if (**fmt == '+')
			params->flags |= FL_PLUS;
		else if (**fmt == ' ')
		{
			if (!(params->flags & FL_PLUS))
				params->flags |= FL_SPACE;
		}
		else if (**fmt == '#')
			params->flags |= FL_HASH;
		else
			break ;
		(*fmt)++;
	}
}

static	void		p_width(char **fmt, t_params *params, va_list *ap)
{
	if (is_digit(**fmt))
	{
		while (is_digit(**fmt))
		{
			params->width = 10 * params->width + (**fmt - '0');
			(*fmt)++;
		}
	}
	else if (**fmt == '*')
	{
		params->width = va_arg(*ap, int);
		if (params->width < 0)
		{
			params->width *= -1;
			params->flags |= FL_Z_BLOCK;
			params->flags |= FL_MINUS;
		}
		(*fmt)++;
	}
}

static	int			p_precision(char **fmt, t_params *params, va_list *ap)
{
	if (**fmt == '.')
	{
		(*fmt)++;
		if (is_digit(**fmt))
		{
			params->precision = 0;
			while (is_digit(**fmt))
			{
				params->precision = 10 * params->precision + (**fmt - '0');
				(*fmt)++;
			}
		}
		else if (**fmt == '*')
		{
			params->precision = va_arg(*ap, int);
			(*fmt)++;
		}
		else
			params->precision = 0;
	}
	if (is_type(**fmt))
		params->type = *(*fmt)++;
	else
		return (1);
	return (0);
}

static	int			parse(char *fmt, t_params *params, va_list *ap)
{
	int len;
	int temp;

	len = 0;
	while (*fmt)
	{
		if (*fmt != '%')
		{
			ft_putchar(*fmt++);
			len++;
			continue;
		}
		fmt++;
		params->width = 0;
		params->flags = FL_NONE;
		params->precision = -1;
		params->type = ' ';
		p_flags(&fmt, params);
		p_width(&fmt, params, ap);
		if (p_precision(&fmt, params, ap) || ((temp = print(params, ap)) == -1))
			return (-1);
		len += temp;
	}
	return (len);
}

int					ft_printf(const char *fmt, ...)
{
	va_list		ap;
	int			len;
	t_params	params;

	va_start(ap, fmt);
	len = parse((char *)fmt, &params, &ap);
	va_end(ap);
	return (len);
}
