#include "fract_ol.h"
#include <stdlib.h>

t_mlx_box	start_window(int h, int w, char *title)
{
	t_mlx_box	out;

	out.h = h;
	out.w = w;
	out.zoom = ZOOM_DEFAULT;
	out.center = (t_complex){0};
	out.base = mlx_init();
	out.window = mlx_new_window(out.base, out.h, out.w, title);
	out.image_buffer = (unsigned char *)mlx_get_data_addr(out.image, \
						&out.pixel_bits, &out.image_width, &out.endian);
	return (out);
}

int	stop_window(t_mlx_box *box)
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
