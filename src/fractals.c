/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   fractals.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/06 11:12:44 by mde-beer       #+#    #+#                */
/*   Updated: 2024/11/06 11:17:55 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include <math.h>
#include <string.h>

int	calc_julia(t_complex point, t_complex constant)
{
	t_complex	value;
	int			iterations;

	value = point;
	iterations = 0;
	while (get_distance((t_complex){0}, value) < 2.0 && ++iterations < MAX_ITER)
		value = add(complex_power(value, 2), constant);
	return (iterations);
}

int	calc_burning_ship(t_complex point, t_complex constant)
{
	t_complex	value;
	t_complex	abs_value;
	int			iterations;

	value = point;
	iterations = 0;
	while (get_distance((t_complex){0}, value) < 2.0 && ++iterations < MAX_ITER)
	{
		abs_value = (t_complex){.r = fabsl(value.r), .i = fabsl(value.i)};
		value = add(complex_power(abs_value, 2), constant);
	}
	return (iterations);
}

int	calc_lyapunov(t_complex point, char *sequence, t_mlx_box box)
{
	long double			value;
	long double			sum;
	const int			limit = ft_strlen(sequence);
	int					iterations;

	value = 0.5;
	iterations = -1;
	sum = 0.0;
	while (++iterations < MAX_ITER)
	{
		if (sequence[iterations % limit] == 'A')
		{
			value = (point.r * 4.0 / box.w) * value * (1 - value);
			sum += logl(fabsl((point.r * 4.0 / box.w) * (1 - 2 * value)));
		}
		else
		{
			value = (point.i * 4.0 / box.h) * value * (1 - value);
			sum += logl(fabsl((point.i * 4.0 / box.h) * (1 - 2 * value)));
		}
	}
	if (sum / MAX_ITER < 0)
		return ((int)(255 * (1 + sum / MAX_ITER)));
	return (0);
}
