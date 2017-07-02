//
// Created by Anastasiia Trepyton on 7/2/17.
//

#include "rt.h"

t_vec3 cone_norm_cut(void *data, t_vec3 hitpoint)
{
	t_cone *c = (t_cone *)data;

	if (c->t_final != c->t_top_cap && c->t_final != c->t_low_cap)
		return (cone_norm(data, hitpoint));
	else if (c->t_low_cap == c->t_final)
		return (vec3_norm(vec3_invert(c->axis)));
	else if (c->t_top_cap == c->t_final)
		return (vec3_norm(c->axis));
	return vec3_create(0, 0, 0);
}

int intersect_cone_cut(t_ray r, void *s, double *t)
{
	t_cone *c;
	t_cone cone;
	double tga;
	t_vec3 hitpoint;

	c = (t_cone *)s;
	cone.p1 = vec3_add(c->p1, vec3_mult(vec3_mult(vec3_sub(c->p2, c->p1), c->r1), 1 /(c->r1 - c->r2)));
	cone.axis = vec3_sub(c->p2, c->p1);
	tga = (c->r1 - c->r2) / vec3_length(cone.axis);
	cone.axis = vec3_norm(cone.axis);
	cone.angle = atan(tga) * 180 / M_PI;
	c->t_top_cap = 0;
	c->t_low_cap = 0;
	c->t_final = 0;
	int ret = 0;
	if (intersect_cone(r, &cone, t))
	{
		hitpoint = vec3_add(r.pos, vec3_mult(r.dir, *t));
		if (vec3_dp(cone.axis, vec3_sub(hitpoint, c->p1)) > 0 &&
			vec3_dp(cone.axis, vec3_sub(hitpoint, c->p2)) < 0)
			ret = 1;
	}
	t_plane p;
	p.pos = c->p1;
	p.normal = cone.axis;
	if (intersect_plane(r, &p, t))
	{
		hitpoint = vec3_add(r.pos, vec3_mult(r.dir, *t));
		if((vec3_dp(hitpoint, hitpoint) - vec3_dp(hitpoint, c->p1) * 2
			+ vec3_dp(c->p1, c->p1)) < pow(c->r1, 2))
		{
			ret = 1;
			c->t_top_cap = *t;
		}
	}
	p.pos = c->p2;
	if (intersect_plane(r, &p, t))
	{
		hitpoint = vec3_add(r.pos, vec3_mult(r.dir, *t));
		if((vec3_dp(hitpoint, hitpoint) - vec3_dp(hitpoint, c->p2) * 2
			+ vec3_dp(c->p2, c->p2)) < pow(c->r2, 2))
		{
			ret = 1;
			c->t_low_cap = *t;
		}
	}
	c->t_final = *t;
	return ret;
}