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

int	calc_mandelbrot(t_complex point, t_complex constant)
{
	(void)constant;
	return (calc_julia(point, point));
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

#define LYUPANOV_SEQUENCE "ABABAB"

int calc_lyupanov(t_complex point, t_mlx_box box)
{
	const t_complex	ab = {.r = point.r * 4.0 / box.w, \
							.i = point.i * 4.0 / box.h};
	long double			value;
	long double			sum;
	const int			limit = strlen(LYUPANOV_SEQUENCE);
	int					iterations;

	value = 0.5;
	iterations = -1;
	sum = 0.0;
	while (++iterations < MAX_ITER)
	{
		if (LYUPANOV_SEQUENCE[iterations % limit] == 'A')
		{
			value = ab.r * value * (1 - value);
			sum += logl(fabsl(ab.r * (1 - 2 * value)));
		}
		else
		{
			value = ab.i * value * (1 - value);
			sum += logl(fabsl(ab.i * (1 - 2 * value)));
		}
	}
	if (sum / MAX_ITER < 0)
		return ((int)(255 * (1 + sum / MAX_ITER)));
	return (0);
}
