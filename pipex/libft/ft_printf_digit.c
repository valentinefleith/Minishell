/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_digit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:13:27 by luvallee          #+#    #+#             */
/*   Updated: 2024/03/08 16:50:49 by luvallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nb_size(unsigned long long nb, int base)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= base;
		i++;
	}
	return (i);
}

char	*ft_str_reverse(char *buffer, int size)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = size - 1;
	while (i <= j)
	{
		temp = buffer[i];
		buffer[i] = buffer[j];
		buffer[j] = temp;
		i++;
		j--;
	}
	buffer[size] = '\0';
	return (buffer);
}

char	*ft_itoa_base(unsigned long long nb, int base, char specifier)
{
	char	*buffer;
	int		size;
	int		i;
	int		temp;

	size = ft_nb_size(nb, base);
	buffer = malloc(sizeof(char) * (size + 1));
	if (!buffer)
		return (NULL);
	if (nb == 0)
		buffer[0] = '0';
	i = 0;
	temp = 0;
	while (nb != 0)
	{
		temp = nb % base;
		if (temp > 9 && specifier == 'X')
			buffer[i++] = (temp - 10) + 'A';
		else if (temp > 9 && specifier == 'x')
			buffer[i++] = (temp - 10) + 'a';
		else
			buffer[i++] = temp + '0';
		nb /= base;
	}
	return (ft_str_reverse(buffer, size));
}

int	ft_putnbr(long long nb)
{
	int	count;

	count = 0;
	if (nb < 0)
	{
		write(1, "-", 1);
		return (ft_putnbr(-nb) + 1);
	}
	if (nb >= 10)
	{
		count = ft_putnbr(nb / 10);
		return (count + ft_putnbr(nb % 10));
	}
	else
		return (count + ft_printf_char(nb + '0'));
	return (count);
}

int	ft_printf_digit(long long nb, int base, char specifier)
{
	int		count;
	char	*new;

	count = 0;
	new = NULL;
	if (nb < 0 && (specifier == 'd' || specifier == 'i'))
	{
		count += ft_putnbr(nb);
	}
	else
	{
		new = ft_itoa_base(nb, base, specifier);
		count += ft_printf_string(new);
		free(new);
	}
	return (count);
}
