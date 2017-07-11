/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynome_4_resolve_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhorbach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 16:11:51 by vhorbach          #+#    #+#             */
/*   Updated: 2017/07/10 16:24:53 by vhorbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		solve_depressed_quartic_3(t_polynome4 *solve, double *results)
{
	solve->d_quad.p = sqrt(solve->d_quad.helper_results[0]);
	solve->d_quad.quadratic_factor[0] = solve->d_quad.c +
		solve->d_quad.p * solve->d_quad.p - solve->d_quad.d / solve->d_quad.p;
	solve->d_quad.quadratic_factor[1] = 2 * solve->d_quad.p;
	solve->d_quad.quadratic_factor[2] = 2;
	solve->d_quad.num_results = solve_real_poly_1(2,
						solve->d_quad.quadratic_factor, results, solve);
	solve->d_quad.quadratic_factor[0] = solve->d_quad.c +
		solve->d_quad.p * solve->d_quad.p + solve->d_quad.d / solve->d_quad.p;
	solve->d_quad.quadratic_factor[1] = -2 * solve->d_quad.p;
}

void		solve_depressed_quartic_2(t_polynome4 *solve, double *results)
{
	int		i;

	solve->d_quad.quadratic[0] = solve->d_quad.e;
	solve->d_quad.quadratic[1] = solve->d_quad.c;
	solve->d_quad.quadratic[2] = 1;
	solve->d_quad.num_quad_results = solve_real_poly_1(2,
			solve->d_quad.quadratic, solve->d_quad.quadratic_results, solve);
	i = -1;
	while (++i < solve->d_quad.num_quad_results)
	{
		solve->d_quad.s = sqrt(solve->d_quad.quadratic_results[i]);
		results[2 * i] = -solve->d_quad.s;
		results[2 * i + 1] = solve->d_quad.s;
	}
}

int			solve_depressed_quartic_1(const double *poly,
									double *results, t_polynome4 *solve)
{
	solve->d_quad.e = poly[0];
	solve->d_quad.d = poly[1];
	solve->d_quad.c = poly[2];
	if (solve->d_quad.d == 0)
	{
		solve_depressed_quartic_2(solve, results);
		return (2 * solve->d_quad.num_quad_results);
	}
	solve->d_quad.helper_cubic[0] = -solve->d_quad.d * solve->d_quad.d;
	solve->d_quad.helper_cubic[1] = solve->d_quad.c * solve->d_quad.c -
								4 * solve->d_quad.e;
	solve->d_quad.helper_cubic[2] = 2 * solve->d_quad.c;
	solve->d_quad.helper_cubic[3] = 1;
	if (solve_real_poly_1(3, solve->d_quad.helper_cubic,
						solve->d_quad.helper_results, solve) < 1)
		return (0);
	solve_depressed_quartic_3(solve, results);
	return (solve->d_quad.num_results + solve_real_poly_1(2,
									solve->d_quad.quadratic_factor, results +
										solve->d_quad.num_results, solve));
}

void		solve_depressed_cubic_2(t_polynome4 *solve)
{
	solve->d_cube.s_real = -solve->d_cube.q / 2;
	solve->d_cube.s_abs = sqrt(solve->d_cube.s_real *
						solve->d_cube.s_real - solve->d_cube.t);
	solve->d_cube.s_phase = atan(sqrt(-solve->d_cube.t) /
								solve->d_cube.s_real) +
							(solve->d_cube.s_real >= 0 ? 0 : M_PI);
	solve->d_cube.u_abs = cubic_root(solve->d_cube.s_abs);
	solve->d_cube.u_phase = solve->d_cube.s_phase / 3.0;
	solve->d_cube.u_real = solve->d_cube.u_abs * cos(solve->d_cube.u_phase);
}

int			solve_depressed_cubic_1(const double *poly,
									double *results, t_polynome4 *solve)
{
	solve->d_cube.q = poly[0];
	solve->d_cube.p = poly[1];
	if (solve->d_cube.p == 0.0)
	{
		results[0] = cubic_root(-solve->d_cube.q);
		return (1);
	}
	solve->d_cube.t = solve->d_cube.q * solve->d_cube.q / 4 + solve->d_cube.p *
										solve->d_cube.p * solve->d_cube.p / 27;
	if (solve->d_cube.t >= 0.0)
	{
		solve->d_cube.u = cubic_root(-solve->d_cube.q /
									2 + sqrt(solve->d_cube.t));
		results[0] = solve->d_cube.u - solve->d_cube.p / 3.0 / solve->d_cube.u;
		return (1);
	}
	solve_depressed_cubic_2(solve);
	results[0] = 2 * solve->d_cube.u_real;
	return (1);
}
