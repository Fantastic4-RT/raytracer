//
// Created by Anastasiia Trepyton on 7/1/17.
//

#include "rt.h"

int intersect_triangle(t_ray r, void *p, double *t)
{
	t_vec3 hitpoint;
	t_plane *pl;
	double dp1;
	double dp2;
	double dp3;

	pl = (t_plane *)p;
	if (intersect_plane(r, p, t))
	{
		hitpoint = vec3_add(r.pos, vec3_mult(r.dir, *t));
		dp1 = vec3_dp(vec3_cross(vec3_sub(pl->p2, pl->pos),
								 vec3_sub(hitpoint, pl->pos)), pl->normal);
		dp2 =vec3_dp(vec3_cross(vec3_sub(pl->p3, pl->p2),
								vec3_sub(hitpoint, pl->p2)), pl->normal);
		dp3 = vec3_dp(vec3_cross(vec3_sub(pl->pos, pl->p3),
								 vec3_sub(hitpoint, pl->p3)), pl->normal);
		if (dp1 >= 0 && dp2 >= 0 && dp3 >=0)
			return (1);
		return (0);

	}
	return (0);
}

int intersect_elips(t_ray r, void *p, double *t)
{
	t_vec3 hitpoint;
	t_plane *pl;
	double dp1;
	double dp2;
	double dp3;

	pl = (t_plane *)p;
	if (intersect_plane(r, p, t))
	{
		hitpoint = vec3_add(r.pos, vec3_mult(r.dir, *t));

		if (dp1 >= 0 && dp2 >= 0 && dp3 >=0)
			return (1);
		return (0);

	}
	return (0);
}