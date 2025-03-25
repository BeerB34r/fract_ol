/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   movement.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/06 14:53:24 by mde-beer       #+#    #+#                */
/*   Updated: 2024/11/06 14:53:25 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int	change_zoom(t_mlx_box *box, int direction)
{
	if (direction < 0)
		box->zoom /= ZOOM_MAGNITUDE;
	else if (direction > 0)
		box->zoom *= ZOOM_MAGNITUDE;
	else
	{
		box->center = 0;
		box->zoom = ZOOM_DEFAULT;
	}
	render_fractal(*box);
	return (0);
}

int	move_center(t_mlx_box *box, double complex vector)
{
	complex double	out;

	out = vector * (MOVE_MAGNITUDE + I * 0);
	out *= (box->zoom + I * 0);
	box->center += out;
	render_fractal(*box);
	return (0);
}

complex double	coords_to_complex(t_mlx_box box, int x, int y)
{
	complex double	out;

	out = (long double)(x - box.w / 2) / (box.w / 4);
	out += I * ((long double)(y - box.h / 2) / (box.h / 4));
	out *= box.zoom + I * 0;
	out += box.center;
	return (out);
}
