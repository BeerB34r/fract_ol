/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   test.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/02 19:28:13 by mde-beer       #+#    #+#                */
/*   Updated: 2024/11/02 21:46:15 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

#define ZOOM_DEFAULT 1.0
#define ZOOM_MAGNITUDE 1.2
void	render_fractal(t_mlx_box box);

long double	get_distance(t_complex a, t_complex b)
{
	return (hypotl(a.r - b.r, a.i - b.i));
}

t_complex	multiply(t_complex a, t_complex b)
{
	t_complex	out;

	out.r = a.r * b.r - a.i * b.i;
	out.i = a.r * b.i + a.i * b.r;
	return (out);
}

t_complex	add(t_complex a, t_complex b)
{
	return ((t_complex){.r= a.r + b.r, .i= a.i + b.i});
}

t_complex	conjugate(t_complex a)
{
	return ((t_complex){.r= a.r, .i= -a.i});
}

t_complex	complex_power(t_complex base, int power)
{
	t_complex	out;
	
	out = (t_complex){1.0, 0.0};
	while (power--)
		out = multiply(out, base);
	return (out);
}
int	change_zoom(t_mlx_box *box, int direction)
{
	if (direction < 0)
		box->zoom /= ZOOM_MAGNITUDE;
	else if (direction > 0)
		box->zoom *= ZOOM_MAGNITUDE;
	else
	{
		box->center = (t_complex){0};
		box->zoom = ZOOM_DEFAULT;
	}
	render_fractal(*box);
	return (0);
}

#define MOVE_MAGNITUDE ((t_complex){.r=0.1, .i=0})

int	change_center(t_mlx_box	*box, t_complex vector)
{
	t_complex	out;

	out = multiply(vector, MOVE_MAGNITUDE);
	out = multiply(out, (t_complex){.r=box->zoom, .i=0});
	box->center = add(box->center, out);
	render_fractal(*box);
	return (0);
}

t_complex	coords_to_complex(t_mlx_box box, int x, int y)
{
	t_complex	out;

	out.r = (long double)(x - box.width / 2) / (box.width / 4);
	out.i = (long double)(y - box.height / 2) / (box.height / 4);
	out = multiply(out, (t_complex){.r=box.zoom, .i=0.0});
	out = add(out, box.center);
	return (out);
}

#define MAX_ITER 255

int	calc_julia(t_complex point, t_complex constant)
{
	t_complex	value;
	int			iterations;
	
	value = point;
	iterations = 0;
	while (get_distance((t_complex){0}, value) < 2.0 \
			&& ++iterations < MAX_ITER)
		value = add(complex_power(value, 2), constant);
	return (iterations);
}

int	calc_mandelbrot(t_complex point)
{
	return (calc_julia(point, point));
}

t_mlx_box	init_mlx(int height, int width, char *title)
{
	t_mlx_box	out;

	out.height = height;
	out.width = width;
	out.zoom = ZOOM_DEFAULT;
	out.center = (t_complex){0};
	out.base = mlx_init();
	out.window = mlx_new_window(out.base, out.height, out.width, title);
	out.image = mlx_new_image(out.base, out.height, out.width);
	out.image_buffer = (unsigned char *)mlx_get_data_addr(out.image,\
															&(out.pixel_bits),\
															&(out.image_width),\
															&(out.endian));
	return (out);
}

void	color_pixel(t_argb color, t_mlx_box box, size_t x, size_t y)
{
	box.image_buffer[x * box.pixel_bits / 8 \
						+ y * box.image_width + 0] = color.b;
	box.image_buffer[x * box.pixel_bits / 8 \
						+ y * box.image_width + 1] = color.g;
	box.image_buffer[x * box.pixel_bits / 8 \
						+ y * box.image_width + 2] = color.r;
	box.image_buffer[x * box.pixel_bits / 8 \
						+ y * box.image_width + 3] = color.a;
}

int	stop_box(t_mlx_box *box)
{
	if (box->image)
		mlx_destroy_image(box->base, box->image);
	if (box->window)
		mlx_destroy_window(box->base, box->window);
	if (box->base)
	{
		mlx_loop_end(box->base);
		mlx_destroy_display(box->base);
		free(box->base);
	}
	exit(0);
}

int	key_event(int keycode, t_mlx_box *box)
{
	if (keycode == 65307) // esc
		return (stop_box(box));
	if (keycode == 65361) // <-
		return (change_center(box, (t_complex){-1, 0}));
	if (keycode == 65363) // ->
		return (change_center(box, (t_complex){1, 0}));
	if (keycode == 65362) // ^
		return (change_center(box, (t_complex){0, -1}));
	if (keycode == 65364) // down
		return (change_center(box, (t_complex){0, 1}));
	if (keycode == 65451)
		return (change_zoom(box, -1));
	if (keycode == 65453)
		return (change_zoom(box, 1));
	if (keycode == 'r')
		return (change_zoom(box, 0));
	return (1);
}

void	render_fractal(t_mlx_box box)
{
	int			x;
	int			y;
	int			val;
	t_complex	coord;

	mlx_clear_window(box.base, box.window);
	x = -1;
	while (++x < box.width)
	{
		y = -1;
		while (++y < box.height)
		{
			coord = coords_to_complex(box, x, y);
			val = calc_julia(coord, (t_complex){.r=-0.8, .i=0.156});
			color_pixel((t_argb){255, val, val, val}, box, x, y);
		}
	}
	mlx_put_image_to_window(box.base, box.window, box.image, 0, 0);
}

int	main(void)
{
	t_mlx_box	box = init_mlx(600, 600, "Mario and Sonic at the Olympic games");
	
	render_fractal(box);
	mlx_hook(box.window, 17, 0, stop_box, &box);
	mlx_key_hook(box.window, key_event, &box);
	mlx_loop(box.base);
}
