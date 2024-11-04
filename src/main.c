/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   main.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/04 17:23:48 by mde-beer       #+#    #+#                */
/*   Updated: 2024/11/04 18:25:01 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <fract_ol.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <libft.h>
#define OPTIONS_FILE "fract_ol_options.md"

void	render_fractal(t_mlx_box box)
{
	int			x;
	int			y;
	int			val;
	t_argb		color;
	t_complex	coord;

	mlx_clear_window(box.base, box.window);
	x = -1;
	while (++x < box.w)
	{
		y = -1;
		while (++y < box.h)
		{
			coord = coords_to_complex(box, x, y);
			val = calc_julia(coord, (t_complex){.r=-0.8, .i=0.156});
			color = box.gradient[val];
			color_pixel(color, box, x, y);
		}
	}
	mlx_put_image_to_window(box.base, box.window, box.image, 0, 0);
}

int	key_event(int keycode, t_mlx_box *box)
{
	if (keycode == 65307) // esc
		return (stop_window(box));
	if (keycode == 65361) // <-
		return (move_center(box, (t_complex){-1, 0}));
	if (keycode == 65363) // ->
		return (move_center(box, (t_complex){1, 0}));
	if (keycode == 65362) // ^
		return (move_center(box, (t_complex){0, -1}));
	if (keycode == 65364) // down
		return (move_center(box, (t_complex){0, 1}));
	if (keycode == 65451)
		return (change_zoom(box, -1));
	if (keycode == 65453)
		return (change_zoom(box, 1));
	if (keycode == 'r')
		return (change_zoom(box, 0));
	return (1);
}

void	attach_hooks(t_mlx_box *box)
{
	mlx_hook(box->window, 17, 0, stop_window, box);
	mlx_key_hook(box->window, key_event, box);
}

void	init_fract_ol(void) // TODO make this less shit
{
	t_argb *const	palette = get_palette();
	t_mlx_box		box;

	if (!palette)
		exit(1);
	box = start_window(600, 600,\
						"Mario:tm: and Sonic:tm: at the Olympic games:tm:",\
						palette);
	render_fractal(box);
	attach_hooks(&box);
	mlx_loop(box.base);
}

int	main(int argc, char **argv) // TODO make this less shit
{
	(void)argc;
	(void)argv;
	init_fract_ol();
}
