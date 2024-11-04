#include <fract_ol.h>
#include <unistd.h>
#include <fcntrl.h>
#include <stdlib.h>
#include <get_next_line.h>
#include <libft.h>

#define OPTIONS_FILE "fract_ol_options.md"

int	display_options(const char *file) 
{
	const int	fd = open(file, O_RDONLY);
	char		*string;

	string = get_next_line(fd);
	while (string)
	{
		write(1, string, ft_strlen(string));
		free(string);
		string = get_next_line(fd);
	}
	close(fd);
	return (0);
}

t_fract_ol_opts	get_fract_ol_opts(const int argc, const char **argv)// TODO make this complete
{
	int	current;
	t_fract_ol_opts	opts;

	current = 1;
	while (current < argc)
	{
		if (argv[current][0] == '-')
	}
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
