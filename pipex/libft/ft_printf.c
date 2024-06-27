/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:07:40 by luvallee          #+#    #+#             */
/*   Updated: 2024/03/30 16:27:38 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_eval_format(va_list arg, char specifier)
{
	if (specifier == 'c')
		return (ft_printf_char(va_arg(arg, int)));
	if (specifier == 's')
		return (ft_printf_string(va_arg(arg, char *)));
	if (specifier == 'p')
		return (ft_printf_adress((unsigned long long)va_arg(arg, void *)));
	if (specifier == 'd' || specifier == 'i')
		return (ft_printf_digit(va_arg(arg, int), 10, 'd'));
	if (specifier == 'u')
		return (ft_printf_digit(va_arg(arg, unsigned int), 10, 'u'));
	if (specifier == 'X')
		return (ft_printf_digit(va_arg(arg, unsigned int), 16, 'X'));
	if (specifier == 'x')
		return (ft_printf_digit(va_arg(arg, unsigned int), 16, 'x'));
	if (specifier == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		return_value;
	va_list	arg;

	return_value = 0;
	va_start(arg, format);
	if (!format)
		return (-1);
	while (*format)
	{
		if (*format == '%')
			return_value += ft_eval_format(arg, *(++format));
		else
			return_value += write(1, format, 1);
		++format;
	}
	va_end(arg);
	return (return_value);
}
