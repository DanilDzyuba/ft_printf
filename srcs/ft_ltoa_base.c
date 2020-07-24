/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clauren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 22:02:19 by clauren           #+#    #+#             */
/*   Updated: 2020/07/24 13:31:48 by clauren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static size_t	ft_number_len(long n, int base)
{
	size_t i;

	i = (n < 0) ? 2 : 1;
	while (n / base)
	{
		n /= base;
		i++;
	}
	return (i);
}

static	void	lower(char *str)
{
	while (*str)
	{
		if (*str <= 90 && *str >= 65)
			*str += 32;
		str++;
	}
}

char			*ft_ltoa_base(long long n, int base, int low)
{
	size_t	len;
	char	*result;
	int		c;

	len = ft_number_len(n, base);
	if (!(result = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	result[len--] = '\0';
	if (n == 0)
		result[0] = '0';
	else if (n < 0 && (n *= -1))
		result[0] = '-';
	while (n > 0)
	{
		c = n % base;
		c = (c > 9) ? c += 7 : c;
		result[len--] = c + '0';
		n /= base;
	}
	if (low)
		lower(result);
	return (result);
}
