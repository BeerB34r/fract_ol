/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   main.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/04 17:23:48 by mde-beer       #+#    #+#                */
/*   Updated: 2024/11/06 14:52:28 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <fract_ol.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <libft.h>

int	compute_fractal(t_fractal fractal, double complex coord, t_mlx_box box)
{
	if (fractal.fractal == mandelbrot)
	{
		if (fractal.julia)
			return (calc_julia(coord, fractal.a));
		return (calc_julia(coord, coord));
	}
	else if (fractal.fractal == burning_ship)
	{
		if (fractal.julia)
			return (calc_burning_ship(coord, fractal.a));
		return (calc_burning_ship(coord, coord));
	}
	else if (fractal.fractal == lyapunov)
		return (calc_lyapunov(coord, fractal.sequence, box));
	return (-1);
}

void	process_color(t_argb *color)
{
	const t_argb	clr1 = (t_argb){.val = CLR1};

	if (!color->val)
		return ;
	(*color).r = (*color).r * clr1.r / 255;
	(*color).g = (*color).g * clr1.g / 255;
	(*color).b = (*color).b * clr1.b / 255;
}

void	render_fractal(t_mlx_box box)
{
	int			x;
	int			y;
	int			val;
	t_argb		color;

	mlx_clear_window(box.base, box.window);
	x = -1;
	while (++x < box.w)
	{
		y = -1;
		while (++y < box.h)
		{
			val = compute_fractal(box.fractal, coords_to_complex(box, x, y), \
									box) * 255;
			color = (t_argb){.a = 0, .r = 255 - val / MAX_ITER, \
									.g = 255 - val / MAX_ITER, \
									.b = 255 - val / MAX_ITER};
			process_color(&color);
			color_pixel(color, box, x, y);
		}
	}
	mlx_put_image_to_window(box.base, box.window, box.image, 0, 0);
}

void	init_fract_ol(t_fract_opts options) // TODO make this less shit
{
	t_mlx_box		box;

	box = start_window(options.h, options.w, options.t, options.parameters);
	render_fractal(box);
	attach_hooks(&box);
	mlx_loop(box.base);
}

int	main(int argc, char **argv) // TODO make this less shit
{
	const t_fract_opts	options = get_options(argc, argv, 1);

	init_fract_ol(options);
}
