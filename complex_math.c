#include "fract_ol.h"
#include <math.h>

t_complex	multiply(t_complex a, t_complex b)
{
	t_complex	out;

	out.r = a.r * b.r - a.i * b.i;
	out.i = a.r * b.i + a.i * b.r;
	return (out);
}

t_complex	add(t_complex a, t_complex b)
{
	return ((t_complex){.r= a.r + b.r, .i= a.i + b.i});
}

t_complex	conjugate(t_complex a)
{
	return ((t_complex){.r= a.r, .i= -a.i});
}

t_complex	complex_power(t_complex base, int power)
{
	t_complex	out;
	
	out = (t_complex){1.0, 0.0};
	while (power--)
		out = multiply(out, base);
	return (out);
}

long double	get_distance(t_complex a, t_complex b)
{
	return (hypotl(a.r - b.r, a.i - b.i));
}
