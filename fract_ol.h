/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   test.h                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/02 19:44:16 by mde-beer       #+#    #+#                */
/*   Updated: 2024/11/02 21:12:42 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H
# include "./minilibx-linux/mlx.h"
# include <stdint.h>

typedef struct s_complex_number
{
	long double	r;
	long double	i;
}	t_complex;

typedef union u_argb_val
{
	uint32_t	value;
	struct
	{
		unsigned char	a;
		unsigned char	r;
		unsigned char	g;
		unsigned char	b;
	};
}	t_argb;

typedef struct s_mlx_values
{
	void			*base;
	void			*window;
	void			*image;
	unsigned char	*image_buffer;
	int				h;
	int				w;
	long double		zoom;
	t_complex		center;
	int				pixel_bits;
	int				image_width;
	int				endian;
}	t_mlx_box;

typedef struct s_fract_ol_options
{
	int	(*formula)(t_complex, t_complex);
	int	window_x;
	int	window_y;
}	t_fract_opts;

// the macros
# define ZOOM_DEFAULT 1.0
# define ZOOM_MAGNITUDE 1.2
# define MOVE_MAGNITUDE 0.1
# define MAX_ITER 255
// fractals
void	render_fractal(t_mlx_box box);
int	calc_julia(t_complex point, t_complex constant);
int	calc_mandelbrot(t_complex point, t_complex constant);
int	calc_burning_ship(t_complex point, t_complex constant);
int	calc_lyupanov(t_complex point, t_mlx_box box);
// movement functions
int			change_zoom(t_mlx_box *box, int direction);
int			move_center(t_mlx_box *box, t_complex vector);
t_complex	coords_to_complex(t_mlx_box box, int x, int y);
// mlx window helpers
t_mlx_box	start_window(int h, int w, char *title);
int			stop_window(t_mlx_box *box);
void		color_pixel(t_argb color, t_mlx_box box, int x, int y);
// complex number arithmetic
t_complex	multiply(t_complex a, t_complex b);
t_complex	add(t_complex a, t_complex b);
t_complex	conjugate(t_complex a);
t_complex	complex_power(t_complex base, int power);
long double	get_distance(t_complex a, t_complex b);
#endif
