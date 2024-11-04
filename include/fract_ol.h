/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   fract_ol.h                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/02 19:44:16 by mde-beer       #+#    #+#                */
/*   Updated: 2024/11/04 17:37:06 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H
# include <mlx.h>
# include <stdint.h>

typedef struct s_complex_number
{
	long double	r;
	long double	i;
}	t_complex;

typedef union u_argb_val
{
	uint32_t	val;
	struct
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
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
	t_argb			*gradient;
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
# define COLR1 0xFFBE0B
# define COLR2 0xFB5607
# define COLR3 0xFF006E
# define COLR4 0x8338EC
# define COLR5 0x3A86FF
# define NUM_COLORS 5
# define MAX_ITER 255
# define COLOR_STEP 51 // MAX_COLORS / NUM_COLOR

// fractals
void		render_fractal(t_mlx_box box);
int			calc_julia(t_complex point, t_complex constant);
int			calc_mandelbrot(t_complex point, t_complex constant);
int			calc_burning_ship(t_complex point, t_complex constant);
int			calc_lyupanov(t_complex point, t_mlx_box box);
// movement functions
int			change_zoom(t_mlx_box *box, int direction);
int			move_center(t_mlx_box *box, t_complex vector);
t_complex	coords_to_complex(t_mlx_box box, int x, int y);
// mlx window helpers
t_mlx_box	start_window(int h, int w, char *title, t_argb *colors);
int			stop_window(t_mlx_box *box);
void		color_pixel(t_argb color, t_mlx_box box, int x, int y);
int			key_event(int keycode, t_mlx_box *box);
t_argb		*get_palette(void);
t_argb		*get_gradient(t_argb colors[NUM_COLORS]);
// complex number arithmetic
t_complex	multiply(t_complex a, t_complex b);
t_complex	add(t_complex a, t_complex b);
t_complex	conjugate(t_complex a);
t_complex	complex_power(t_complex base, int power);
long double	get_distance(t_complex a, t_complex b);
#endif
