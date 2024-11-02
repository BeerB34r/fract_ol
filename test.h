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

#ifndef TEST_H
# define TEST_H
# include "./minilibx-linux/mlx.h"

typedef	struct	s_complex_number
{
	long double	r;
	long double	i;
}	t_complex;

typedef struct	s_argb_val
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_argb;

typedef struct	s_mlx_values
{
	void			*base;
	void			*window;
	void			*image;
	unsigned char	*image_buffer;
	int				height;
	int				width;
	long double		zoom;
	t_complex		center;
	int				pixel_bits;
	int				image_width;
	int				endian;
}	t_mlx_box;

#endif


