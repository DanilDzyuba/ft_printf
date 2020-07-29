/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clauren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:07:40 by clauren           #+#    #+#             */
/*   Updated: 2020/07/25 15:18:45 by clauren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FT_PRINTF_H
# define FT_PRINTF_FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# define FL_NONE		0b00000000
# define FL_MINUS		0b00000001
# define FL_ZERO		0b00000010
# define FL_HASH		0b00000100
# define FL_SPACE		0b00001000
# define FL_PLUS		0b00010000
# define FL_Z_BLOCK		0b10000000

typedef struct		s_params
{
	unsigned char	flags;
	int				width;
	int				precision;
	char			type;
}					t_params;

typedef	struct		s_lens
{
	int				zero_len;
	int				filler_len;
	int				str_len;
	char			f;
}					t_lens;

int					ft_strlen(char *s);
int					is_digit(char c);
int					is_type(char c);
int					ft_putchar(int c);
void				ft_putstr(char *p);
void				print_filler(char c, int n);
int					print_d(t_params *params, va_list *ap);
int					print_uxp(t_params *params, va_list *ap, int low, int base);
int					print(t_params *params, va_list *ap);
char				*ft_ltoa_base(long long n, int base, int low);
int					ft_printf(const char *fmt, ...);
#endif
