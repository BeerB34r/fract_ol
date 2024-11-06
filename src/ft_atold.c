/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_atold.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/06 11:40:07 by mde-beer       #+#    #+#                */
/*   Updated: 2024/11/06 11:54:25 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

long double	ft_atold(char *string)
{
	long double	out_front;
	long double	out_back;
	long double	decimals;
	int			sign;

	out_front = 0;
	out_back = 0;
	sign = 1;
	decimals = 0.1;
	if (*string == '-')
	{
		sign = -1;
		string++;
	}
	while (ft_isdigit(*string))
		out_front = (out_front * 10) + ((*string++ - 0x30) * sign);
	if (*string++ == '.')
	{
		while (ft_isdigit(*string))
		{
			out_back += ((*string++ - 0x30) * sign * decimals);
			decimals /= 10;
		}
	}
	return (out_front + out_back);
}
