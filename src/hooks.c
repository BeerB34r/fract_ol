/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   hooks.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/05 10:24:36 by mde-beer       #+#    #+#                */
/*   Updated: 2024/11/06 12:22:54 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <keys.h>
#include <fract_ol.h>

int	key_event(int keycode, t_mlx_box *box)
{
	if (keycode == K_ESC || keycode == 'q')
		return (stop_window(box));
	else if (keycode == K_AR_L || keycode == 'a')
		return (move_center(box, (t_complex){-1, 0}));
	else if (keycode == K_AR_R || keycode == 'd')
		return (move_center(box, (t_complex){1, 0}));
	else if (keycode == K_AR_U || keycode == 'w')
		return (move_center(box, (t_complex){0, -1}));
	else if (keycode == K_AR_D || keycode == 's')
		return (move_center(box, (t_complex){0, 1}));
	else if (keycode == K_NP_PLU || keycode == K_PLUS)
		return (change_zoom(box, -1));
	else if (keycode == K_NP_MIN || keycode == K_MINUS)
		return (change_zoom(box, 1));
	else if (keycode == 'r')
		return (change_zoom(box, 0));
	return (1);
}

int	mouse_event(int keycode, int x, int y, t_mlx_box *box)
{
	if (keycode == M_CLK_L || keycode == M_SCR_D || keycode == M_SCR_U)
		box->center = coords_to_complex(*box, x, y);
	if (keycode == M_SCR_D)
		return (change_zoom(box, -1));
	else if (keycode == M_SCR_U)
		return (change_zoom(box, 1));
	else if (keycode == M_CLK_M)
		return (change_zoom(box, 0));
	return (1);
}

void	attach_hooks(t_mlx_box *box)
{
	mlx_hook(box->window, 17, 0, stop_window, box);
	mlx_mouse_hook(box->window, mouse_event, box);
	mlx_key_hook(box->window, key_event, box);
}
