//
// Created by Anastasiia Trepyton on 6/14/17.
//

#include "rt.h"

t_vec3 sphere_norm(void *data, t_vec3 hitpoint)
{
	t_sphere *s = (t_sphere *)data;
	return (vec3_norm(vec3_sub(hitpoint, s->pos)));
}

t_vec3 plane_norm(void *data, t_vec3 hitpoint)
{
	t_vec3 a;

	a = hitpoint;
	t_plane *p = (t_plane *)data;
	return (vec3_norm(p->normal));
}

t_vec3 cone_norm(void *data, t_vec3 hitpoint)
{
	t_vec3 tmp;
	t_cone *c = (t_cone*)data;
	t_vec3	n;
	t_vec3	n1;

	n = vec3_norm(vec3_sub(hitpoint, vec3_add(c->p1, vec3_mult(c->axis,
				vec3_length(vec3_sub(hitpoint,c->p1)) /
			vec3_dp(c->axis, vec3_norm(vec3_sub(hitpoint, c->p1)))))));
	tmp = vec3_sub(hitpoint, c->p1);//position
	double t = vec3_length(tmp) / (vec3_dp(c->axis, vec3_norm(tmp)));
	n1 = vec3_norm(vec3_sub(hitpoint, vec3_add(c->p1, vec3_mult(c->axis, t))));
	return (n1);
}

t_vec3 cylinder_norm(void * data, t_vec3 hitpoint)
{
	t_cyl *c = (t_cyl *)data;
	double t = vec3_dp(vec3_sub(hitpoint, c->p1), c->axis);
	return (vec3_norm(vec3_sub(hitpoint, vec3_add(c->p1,vec3_mult(c->axis, t)))));

}


t_mattype get_material_type(t_material mat)
{
	if (mat.refract != 0 && mat.reflect != 0)
		return (REFLECT_REFRACT);
	else if (mat.refract == 0 && mat.reflect != 0)
		return (REFLECT);
	else
		return (LAMBERT);
}