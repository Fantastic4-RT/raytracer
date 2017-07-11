/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynome_4_resolve_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhorbach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 16:11:32 by vhorbach          #+#    #+#             */
/*   Updated: 2017/07/10 16:23:02 by vhorbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		calc_binomials(int num_binoms, int stride, double *dst)
{
	int		prev_row_idx;
	int		row_idx;
	int		col;
	int		row;

	row = -1;
	while (++row < num_binoms)
	{
		row_idx = row * stride;
		prev_row_idx = (row - 1) * stride;
		dst[row_idx] = 1;
		col = 0;
		while (++col < row)
			dst[row_idx + col] = dst[prev_row_idx + col - 1] +
							dst[prev_row_idx + col];
		dst[row_idx + row] = 1;
	}
}

void		calc_powers(double x, int max_power, double *dst)
{
	int i;

	dst[0] = 1.0;
	if (max_power >= 1)
		dst[1] = x;
	i = 1;
	while (++i <= max_power)
		dst[i] = x * dst[i - 1];
}

int			solve_depressed_poly(int degree, const double *poly,
									double *results, t_polynome4 *solve)
{
	if (degree > 0 && poly[0] == 0.0)
	{
		results[0] = 0;
		return (1 + solve_depressed_poly(degree - 1,
									poly + 1, results + 1, solve));
	}
	if (degree == 4)
		return (solve_depressed_quartic_1(poly, results, solve));
	else if (degree == 3)
		return (solve_depressed_cubic_1(poly, results, solve));
	else if (degree == 2)
		return (solve_depressed_quadratic(poly, results));
	else if (degree == 1)
	{
		results[0] = 0.0;
		return (solve_depressed_quadratic(poly, results));
	}
	else if (degree == 0)
		return (0);
	else
		return (-1);
}

double		cubic_root(double x)
{
	double	t;

	t = pow(fabs(x), 1.0 / 3.0);
	return (x >= 0.0 ? t : -t);
}

int			solve_depressed_quadratic(const double *poly, double *results)
{
	double t;

	t = sqrt(-poly[0]);
	results[0] = -t;
	results[1] = t;
	return (2);
}
