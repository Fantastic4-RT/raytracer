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

	pl = (t_plane *)p;
	if (intersect_plane(r, p, t))
	{
		hitpoint = vec3_add(r.pos, vec3_mult(r.dir, *t));
		if ((vec3_dp(hitpoint, hitpoint) - 2 * vec3_dp(hitpoint, pl->pos) +
				vec3_dp(pl->pos, pl->pos)) < pow(pl->rad, 2))
			return (1);
		return (0);
	}
	return (0);
}

int intersect_mesh(t_ray r, void *p, double *t)
{
	t_plane *pl;
	t_plane tr1;
	t_plane tr2;

	pl = (t_plane *)p;
	double tmp1 = *t;
	double tmp2 = *t;
	tr1.normal = pl->normal;
	tr2.normal = pl->normal;
	tr1.pos = pl->p2;
	tr2.pos = pl->p4;
	tr1.p2 = pl->p3;
	tr2.p2 = pl->pos;
	tr1.p3 = pl->pos;
	tr2.p3 = pl->p3;

	int ret1 = intersect_triangle(r, &tr2, &tmp1);
	int ret2 = intersect_triangle(r, &tr1, &tmp2);
	if (ret1 != 0 || ret2 != 0)
		printf("%d %d\n", ret1, ret2);
	if (ret1 || ret2)
		return (1);
	return (0);
}