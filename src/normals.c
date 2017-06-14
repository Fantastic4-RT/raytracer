//
// Created by Anastasiia Trepyton on 6/14/17.
//

#include "../includes/rt.h"

t_vec3 sphere_norm(void *data, t_vec3 hitpoint)
{
	t_sphere *s = (t_sphere *)data;
	return (vec3_sub(hitpoint, s->pos));
}

t_vec3 plane_norm(void *data, t_vec3 hitpoint)
{
	t_plane *p = (t_plane *)data;
	return (p->normal);
}

t_vec3 cone_norm(void *data, t_vec3 hitpoint)
{
	t_vec3 tmp;
	t_cone *c = (t_cone*)data;
	tmp = vec3_sub(hitpoint, c->p1);//position
	double t = vec3_length(tmp) / (vec3_dp(c->axis, vec3_norm(tmp)));
	return (vec3_sub(hitpoint, vec3_add(c->p1, vec3_mult(c->axis, t))));
}

t_vec3 cylinder_norm(void * data, t_vec3 hitpoint)
{
	t_cyl *c = (t_cyl *)data;
	double t = vec3_dp(vec3_sub(hitpoint, c->p1), c->axis);
	return (vec3_sub(hitpoint, vec3_add(c->p1,vec3_mult(c->axis, t))));

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