/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   window_utils.c                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/04 10:35:00 by mde-beer       #+#    #+#                */
/*   Updated: 2024/11/06 13:08:54 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <fract_ol.h>
#include <libft.h>
#include <mlx.h>
#include <stdlib.h>

t_mlx_box	start_window(int h, int w, char *title, t_fractal fractal)
{
	t_mlx_box	out;

	out.h = h;
	out.w = w;
	out.zoom = ZOOM_DEFAULT;
	out.center = 0;
	out.fractal = fractal;
	out.base = mlx_init();
	if (!(out.base))
		stop_window(&out);
	out.window = mlx_new_window(out.base, out.w, out.h, title);
	if (!(out.window))
		stop_window(&out);
	out.image = mlx_new_image(out.base, out.w, out.h);
	if (!(out.image))
		stop_window(&out);
	out.image_buffer = (unsigned char *)mlx_get_data_addr(out.image, \
						&(out.pixel_bits), &(out.image_width), &(out.endian));
	if (!(out.image_buffer))
		stop_window(&out);
	return (out);
}

int	stop_window(t_mlx_box *box)
{
	if (box->window)
		mlx_destroy_window(box->base, box->window);
	if (box->image)
		mlx_destroy_image(box->base, box->image);
	if (box->base)
	{
		mlx_loop_end(box->base);
		mlx_destroy_display(box->base);
		free(box->base);
	}
	exit(0);
}

void	color_pixel(t_argb color, t_mlx_box box, int x, int y)
{
	const int	pixel_bytes = box.pixel_bits / 8;
	const int	true_x = x * pixel_bytes;
	const int	true_y = y * box.image_width;
	const int	pixel = true_x + true_y;

	if (box.endian)
	{
		box.image_buffer[pixel + 0] = color.a;
		box.image_buffer[pixel + 1] = color.r;
		box.image_buffer[pixel + 2] = color.g;
		box.image_buffer[pixel + 3] = color.b;
	}
	else
	{
		box.image_buffer[pixel + 0] = color.b;
		box.image_buffer[pixel + 1] = color.g;
		box.image_buffer[pixel + 2] = color.r;
		box.image_buffer[pixel + 3] = color.a;
	}
}
