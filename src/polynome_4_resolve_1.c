/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynome_4_resolve.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhorbach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 16:17:17 by vhorbach          #+#    #+#             */
/*   Updated: 2017/07/10 16:22:14 by vhorbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		solve_real_poly_2(int degree, const double *poly,
							t_polynome4 *solve, double a)
{
	int		i;

	i = -1;
	while (++i < degree)
		solve->normalized_poly[i] = poly[i] / a;
	solve->normalized_poly[degree] = 1.0;
}

int			solve_real_poly_1(int degree, const double *poly,
							double *results, t_polynome4 *solve)
{
	double	a;
	int		i;
	int		num_results;

	a = poly[degree];
	if (a == 0)
		return (solve_real_poly_1(degree - 1, poly, results, solve));
	if (degree > MAX_DEGREE)
		return (-1);
	if (degree > 2 && stableness_score(poly[degree],
					poly[degree - 1]) > stableness_score(poly[0], poly[1]))
	{
		i = -1;
		while (++i <= degree)
			solve->rev_poly[i] = poly[degree - i];
		num_results = solve_real_poly_1(degree,
										solve->rev_poly, results, solve);
		i = -1;
		while (++i < num_results)
			results[i] = 1.0 / results[i];
		return (num_results);
	}
	solve_real_poly_2(degree, poly, solve, a);
	return (solve_normalized_poly(degree,
						solve->normalized_poly, results, solve));
}

double		stableness_score(double a, double b)
{
	double	t;

	t = fabs(a / b);
	return (t + 1.0 / t);
}

int			solve_normalized_poly(int degree, const double *poly,
							double *results, t_polynome4 *solve)
{
	double	shifted_coefs[MAX_DEGREE + 1];
	double	shift;
	int		i;
	int		num_results;

	shift = -poly[degree - 1] / (double)degree;
	calc_shifted_coefs(shift, degree, poly, shifted_coefs);
	num_results = solve_depressed_poly(degree, shifted_coefs, results, solve);
	i = -1;
	while (++i < num_results)
		results[i] += shift;
	return (num_results);
}

void		calc_shifted_coefs(double shift, int degree,
						const double *src, double *dst)
{
	double	binomials[MAX_DEGREE + 1][MAX_DEGREE + 1];
	double	shift_powers[MAX_DEGREE + 1];
	int		dst_i;
	int		src_i;

	dst_i = -1;
	while (++dst_i <= degree)
		dst[dst_i] = 0;
	calc_binomials(degree + 1, sizeof(binomials[0]) /
					sizeof(binomials[0][0]), binomials[0]);
	calc_powers(shift, degree, shift_powers);
	src_i = -1;
	while (++src_i <= degree)
	{
		dst_i = -1;
		while (++dst_i <= src_i)
			dst[dst_i] += src[src_i] * shift_powers[src_i - dst_i]
					* binomials[src_i][dst_i];
	}
}
