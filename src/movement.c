#include "fract_ol.h"

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

int	move_center(t_mlx_box *box, t_complex vector)
{
	t_complex	out;

	out = multiply(vector, (t_complex){.r = MOVE_MAGNITUDE, .i = 0});
	out = multiply(out, (t_complex){.r = box->zoom, .i = 0});
	box->center = add(box->center, out);
	render_fractal(*box);
	return (0);
}

t_complex	coords_to_complex(t_mlx_box box, int x, int y)
{
	t_complex	out;

	out.r = (long double)(x - box.w / 2) / (box.w / 4);
	out.i = (long double)(y - box.h / 2) / (box.w / 4);
	out = multiply(out, (t_complex){.r = box.zoom, .i = 0});
	out = add(out, box.center);
	return (out);
}
