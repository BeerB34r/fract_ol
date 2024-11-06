/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_constants.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/05 14:17:25 by mde-beer       #+#    #+#                */
/*   Updated: 2024/11/06 14:40:03 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <fract_ol.h>
#include <libft.h>
#include <stdlib.h>

static void	get_lyapunov_consts(t_fract_opts *options, \
									char **argv, int argc, int *index)
{
	char		*sequence;

	if (*index < argc)
	{
		sequence = argv[(*index)++];
	}
	else
	{
		sequence = "BBBBBBAAAAAA";
	}
	options->parameters.sequence = sequence;
}

static void	get_mandelbrot_consts(t_fract_opts *options, \
									char **argv, int argc, int *index)
{
	t_complex	a;

	if (*index < argc - 1)
	{
		a.r = ft_atold(argv[(*index)++]);
		a.i = ft_atold(argv[(*index)++]);
	}
	else
	{
		a.r = -0.744;
		a.i = 0.148;
	}
	options->parameters.a = a;
}

static void	get_burning_consts(t_fract_opts *options, \
									char **argv, int argc, int *index)
{
	t_complex	a;

	if (*index < argc - 1)
	{
		a.r = ft_atold(argv[(*index)++]);
		a.i = ft_atold(argv[(*index)++]);
	}
	else
	{
		a.r = -0.744;
		a.i = 0.148;
	}
	options->parameters.a = a;
}

void	set_constants(t_fract_opts *options)
{
	int	bypass;

	bypass = 1;
	options->parameters.julia = falsey;
	if (options->parameters.fractal == lyapunov)
		return (get_lyapunov_consts(options, NULL, -1, &bypass));
	else if (options->parameters.fractal == mandelbrot)
		return (get_mandelbrot_consts(options, NULL, -1, &bypass));
	else if (options->parameters.fractal == burning_ship)
		return (get_burning_consts(options, NULL, -1, &bypass));
	else
		exit(1);
}

void	get_constants(t_fract_opts *options, char **argv, int argc, int *index)
{
	(*index)++;
	options->parameters.julia = truey;
	if (options->parameters.fractal == lyapunov)
		return (get_lyapunov_consts(options, argv, argc, index));
	else if (options->parameters.fractal == mandelbrot)
		return (get_mandelbrot_consts(options, argv, argc, index));
	else if (options->parameters.fractal == burning_ship)
		return (get_burning_consts(options, argv, argc, index));
	else
		exit(1);
}
