#include "fract_ol.h"
#include <unistd.h>
#include <fcntrl.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "libft.h"

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

t_fract_ol_opts	get_fract_ol_opts(const int argc, const char **argv)
{
	int	current;
	t_fract_ol_opts	opts;

	current = 1;
	while (current < argc)
	{
		if (argv[current][0] == '-')
	}
}

int	main(int argc, char **argv)
{
	t_fract_ol_opts	opts;

	if (argc < 2)
		return (print_file(OPTIONS_FILE));
	opts = get_fract_ol_opts(argc, argv);
	init_fract_ol(opts);
}
