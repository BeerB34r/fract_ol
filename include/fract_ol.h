/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   fract_ol.h                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/02 19:44:16 by mde-beer       #+#    #+#                */
/*   Updated: 2024/11/06 12:59:20 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H
# include <mlx.h>
# include <stdint.h>
# include <libft.h>

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

enum e_fractals
{
	mandelbrot,
	burning_ship,
	lyapunov
};

typedef struct s_fractal_specification
{
	enum e_fractals	fractal;
	enum e_bool		julia;
	t_complex		a;
	t_complex		b;
	char			*sequence;
}	t_fractal;

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
	t_fractal		fractal;
}	t_mlx_box;

typedef struct s_fract_ol_options
{
	int				h;
	int				w;
	char			*t;
	t_fractal		parameters;
}	t_fract_opts;

// the macros
# define ZOOM_DEFAULT 1.0
# define ZOOM_MAGNITUDE 1.2
# define MOVE_MAGNITUDE 0.1
# define MAX_ITER 90
# define CLR1 0xFF46A2
# define OPTIONS_FILE "fract_ol_options.md"

// option parsing
void			get_geometry(t_fract_opts *options, \
								char **argv, int argc, int *index);
void			get_title(t_fract_opts *options, \
								char **argv, int argc, int *index);
void			get_fractal(t_fract_opts *options, \
								char **argv, int argc, int *index);
void			get_constants(t_fract_opts *options, \
								char **argv, int argc, int *index);
void			set_constants(t_fract_opts *options);
t_fract_opts	get_options(int argc, char **argv);
// fractals
void			render_fractal(t_mlx_box box);
int				calc_julia(t_complex point, t_complex constant);
int				calc_burning_ship(t_complex point, t_complex constant);
int				calc_lyapunov(t_complex point, char *sequence, t_mlx_box box);
// movement functions
int				change_zoom(t_mlx_box *box, int direction);
int				move_center(t_mlx_box *box, t_complex vector);
t_complex		coords_to_complex(t_mlx_box box, int x, int y);
// mlx window helpers
t_mlx_box		start_window(int h, int w, char *title, t_fractal fractal);
int				stop_window(t_mlx_box *box);
void			color_pixel(t_argb color, t_mlx_box box, int x, int y);
int				key_event(int keycode, t_mlx_box *box);
int				mouse_event(int keycode, int x, int y, t_mlx_box *box);
void			attach_hooks(t_mlx_box *box);
// complex number arithmetic
t_complex		multiply(t_complex a, t_complex b);
t_complex		add(t_complex a, t_complex b);
t_complex		conjugate(t_complex a);
t_complex		complex_power(t_complex base, int power);
long double		get_distance(t_complex a, t_complex b);
long double		ft_atold(char *string);
#endif
