//
// Created by Anastasiia Trepyton on 6/14/17.
//

#include "rt.h"

t_vec3 sphere_norm(void *data, t_vec3 hitpoint)
{
	t_sphere *s = (t_sphere *)data;
	return (vec3_norm(vec3_sub(hitpoint, s->pos)));
}

t_vec3 sphere_norm_cut(void *data, t_vec3 hitpoint)
{
	t_sphere *s = (t_sphere *)data;

	if (s->hit_obj == 0)
		return (vec3_norm(vec3_sub(hitpoint, s->pos)));
	else
		return (vec3_norm(vec3_sub(s->p1, s->pos)));
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

	tmp = vec3_sub(hitpoint, c->p1);
	double t = vec3_length(tmp) / (vec3_dp(c->axis, vec3_norm(tmp)));
	n = vec3_norm(vec3_sub(hitpoint, vec3_add(c->p1, vec3_mult(c->axis, t))));
	return (n);
}

t_vec3 cylinder_norm(void *data, t_vec3 hitpoint)
{
	t_cyl *c = (t_cyl *)data;
	double t = vec3_dp(vec3_sub(hitpoint, c->p1), c->axis);
	return (vec3_norm(vec3_sub(hitpoint, vec3_add(c->p1, vec3_mult(c->axis, t)))));
}


t_vec3	parab_norm(void *data, t_vec3 hitpoint)
{
	t_parab *p;
	t_vec3 x;
	t_vec3 n;
	double m;

	p = (t_parab *) data;
	x = vec3_sub(hitpoint, p->pos);
	m = vec3_dp(x, p->axis);
	n = vec3_sub(x, vec3_mult(p->axis, m + p->k));
	return (vec3_norm(n));
}
t_vec3 cylinder_norm_cut(void *data, t_vec3 hitpoint)
{
    t_cyl *c = (t_cyl *)data;

    if (c->t_final != c->t_top_cap && c->t_final != c->t_low_cap)
        return (cylinder_norm(data, hitpoint));
    else if (c->t_low_cap == c->t_final)
        return (vec3_norm(vec3_invert(c->axis)));
    else
        return (vec3_norm(c->axis));
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