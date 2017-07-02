//
// Created by Anastasiia Trepyton on 7/2/17.
//

#include "rt.h"

double    ft_check_min(double t1, double t2)
{
	double temp;

	temp = 0;
	if (t1 != 0 && t2 != 0)
		temp = fmin(t1, t2);
	else if (t1 != 0 || t2 != 0)
		temp = fmax(t1, t2);
	return (temp);
}

t_vec3 cone_norm_cut(void *data, t_vec3 hitpoint)
{
	t_cone *c = (t_cone *)data;
	t_vec3 tmp;
	t_vec3	n;

	if (c->cone_hit == 1)
	{
		tmp = vec3_sub(hitpoint, c->apex);//position
		double t = vec3_length(tmp) / (vec3_dp(c->axis, vec3_norm(tmp)));
		n = vec3_norm(vec3_sub(hitpoint, vec3_add(c->apex, vec3_mult(c->axis, t))));
		return (n);
	}
	else if (c->cone_hit == 3)
		return (vec3_norm(vec3_invert(c->axis)));
	else
		return (vec3_norm(c->axis));

}

int intersect_cone_cut(t_ray r, void *s, double *t)
{
	t_cone *c;
	t_cone cone;
	t_vec3 hitpoint;

	c = (t_cone *)s;
	cone.p1 = vec3_add(c->p1, vec3_mult(vec3_mult(vec3_sub(c->p2, c->p1), c->r1), 1 /(c->r1 - c->r2)));
	cone.axis = vec3_sub(c->p2, c->p1);
	cone.angle = atan((c->r1 - c->r2) / vec3_length(cone.axis)) * 180 / M_PI;
	c->axis = cone.axis;
	c->apex = cone.p1;
	c->angle = cone.angle;
	int ret = 0;
	double tmp[3];
	tmp[0] = *t;
	if (intersect_cone(r, &cone, &tmp[0]))
	{
		hitpoint = vec3_add(r.pos, vec3_mult(r.dir, tmp[0]));
		if (vec3_dp(cone.axis, vec3_sub(hitpoint, c->p1)) > 0 &&
			vec3_dp(cone.axis, vec3_sub(hitpoint, c->p2)) < 0)
		{
			if (tmp[0] < *t)
				c->cone_hit = 1;
			ret = 1;
		}
	}
	t_plane p;
	p.pos = c->p2;
	p.normal = cone.axis;
	tmp[1] = *t;
	if (intersect_plane(r, &p, &tmp[1]))
	{
		hitpoint = vec3_add(r.pos, vec3_mult(r.dir, tmp[1]));
		if((vec3_dp(hitpoint, hitpoint) - vec3_dp(hitpoint, c->p2) * 2
			+ vec3_dp(c->p2, c->p2)) < pow(c->r2, 2))
		{
			ret = 1;
			if (tmp[1] < tmp[0])
				c->cone_hit = 3;
		}
	}
	p.pos = c->p1;
	tmp[2] = *t;
	if (intersect_plane(r, &p, &tmp[2]))
	{
		hitpoint = vec3_add(r.pos, vec3_mult(r.dir, tmp[2]));
		if((vec3_dp(hitpoint, hitpoint) - vec3_dp(hitpoint, c->p1) * 2
			+ vec3_dp(c->p1, c->p1)) < pow(c->r1, 2))
		{
			ret = 1;
			if (tmp[2] < tmp[0])
				c->cone_hit = 2;
		}
	}
	*t = ft_check_min(*t, ft_check_min(tmp[0], ft_check_min(tmp[1], tmp[2])));
	return ret;
}