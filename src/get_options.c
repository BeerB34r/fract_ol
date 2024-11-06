/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_options.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/05 14:45:13 by mde-beer       #+#    #+#                */
/*   Updated: 2024/11/06 14:53:12 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <fract_ol.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void	get_geometry(t_fract_opts *options, char **argv, int argc, int *index)
{
	(*index)++;
	if (*index < argc - 1)
	{
		options->h = ft_atoi(argv[(*index)++]);
		options->w = ft_atoi(argv[(*index)++]);
	}
	else
		exit(1);
}

void	get_title(t_fract_opts *options, char **argv, int argc, int *index)
{
	(*index)++;
	if (*index < argc)
		options->t = argv[(*index)++];
	else
		exit(1);
}

void	get_fractal(t_fract_opts *options, char **argv, int argc, int *index)
{
	(*index)++;
	if (*index < argc)
	{
		if (argv[*index][0] == 'm')
			options->parameters.fractal = mandelbrot;
		else if (argv[*index][0] == 'b')
			options->parameters.fractal = burning_ship;
		else if (argv[*index][0] == 'l')
			options->parameters.fractal = lyapunov;
		else
			exit(1);
		(*index)++;
	}
	else
		exit(1);
}

void	display_options(void)
{
	const int	fd = open(OPTIONS_FILE, O_RDONLY);
	char		*str;

	str = get_next_line(fd);
	while (str)
	{
		write(1, str, ft_strlen(str));
		free(str);
		str = get_next_line(fd);
	}
	exit(0);
}

t_fract_opts	get_options(int argc, char **argv, int index)
{
	t_fract_opts	options;

	if (argc < 3)
		display_options();
	options.parameters.julia = falsey;
	if (index < argc && !ft_strncmp(argv[index], "-g", 2))
		get_geometry(&options, argv, argc, &index);
	else
	{
		options.w = 600;
		options.h = 600;
	}
	if (index < argc && !ft_strncmp(argv[index], "-t", 2))
		get_title(&options, argv, argc, &index);
	else
		options.t = "fract_ol";
	if (index < argc && !ft_strncmp(argv[index], "-f", 2))
		get_fractal(&options, argv, argc, &index);
	else
		exit(1);
	if (index < argc && !ft_strncmp(argv[index], "-c", 2))
		get_constants(&options, argv, argc, &index);
	else
		set_constants(&options);
	return (options);
}
