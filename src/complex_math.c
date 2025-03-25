/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   complex_math.c                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/06 14:38:56 by mde-beer       #+#    #+#                */
/*   Updated: 2024/11/06 14:39:35 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include <math.h>

long double	get_distance(double complex a, double complex b)
{
	return (hypotl(creal(a) - creal(b), (I * cimag(a)) - (I * cimag(b))));
}
