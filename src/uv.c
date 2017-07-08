
#include "rt.h"

void	sphere_uv(t_thread *th, t_main *main)
{
	double phi;
	double theta;

	phi = acos(-vec3_dp(th->obj[main->curr].dir_y, th->obj[main->curr].n));
	th->obj[main->curr].uv.y = phi / M_PI;
	theta = (acos(vec3_dp(th->obj[main->curr].n, th->obj[main->curr].dir_x)) /
		sin(phi)) / (2 * M_PI);
	if (vec3_dp(vec3_cross(th->obj[main->curr].dir_y,
		th->obj[main->curr].dir_x), th->obj[main->curr].n) > 0)
		th->obj[main->curr].uv.x = theta;
	else
		th->obj[main->curr].uv.x = 1 - theta;
}

void	plane_uv(t_thread *th, t_main *main)
{
	t_vec3 nnew;
	t_vec3 a;
	t_vec3 b;
	t_vec3 p;

	nnew = vec3_norm(vec3_sub(th->obj[main->curr].n,
		vec3_create(0.01, 0.01, 0.01)));
	a = vec3_norm(vec3_cross(th->obj[main->curr].n, nnew));
	b = vec3_norm(vec3_cross(a, th->obj[main->curr].n));
	p = vec3_sub(th->obj[main->curr].hitpoint,
				 ((t_plane *)th->obj[main->curr].data)->pos);
	th->obj[main->curr].uv.x = vec3_dp(b, p) / 10;
	th->obj[main->curr].uv.y = vec3_dp(a, p) / 10;
	if (th->obj[main->curr].uv.x < 0 && th->obj[main->curr].texture >= 9)
		th->obj[main->curr].uv.x = TEXT_S + th->obj[main->curr].uv.x;
	if (th->obj[main->curr].uv.y < 0 && th->obj[main->curr].texture >= 9)
		th->obj[main->curr].uv.y = TEXT_S + th->obj[main->curr].uv.y;

}

void	cone_uv(t_thread *th, t_main *main)
{
	t_vec3 pos_hp;
	double proj;
	t_vec3	p;
	t_vec3 c;

	pos_hp = vec3_sub(th->obj[main->curr].hitpoint,
	((t_cone *)th->obj[main->curr].data)->apex);
	proj = vec3_dp(th->obj[main->curr].dir_y, pos_hp);
	p = vec3_mult(((t_cone *)th->obj[main->curr].data)->axis, proj);
	c = vec3_norm(vec3_sub(th->obj[main->curr].hitpoint, p));
	th->obj[main->curr].uv.x = vec3_dp(c, th->obj[main->curr].dir_x);
	th->obj[main->curr].uv.y = proj / M_PI;
	if (th->obj[main->curr].uv.x < 0 && th->obj[main->curr].texture >= 9)
		th->obj[main->curr].uv.x = TEXT_S + th->obj[main->curr].uv.x;
	if (th->obj[main->curr].uv.y < 0 && th->obj[main->curr].texture >= 9)
		th->obj[main->curr].uv.y = TEXT_S + th->obj[main->curr].uv.y;
}

void	cylinder_uv(t_thread *th, t_main *main)
{
	t_vec3 pos_hp;
	double proj;
	t_vec3 p;
	t_vec3 c;
	pos_hp = vec3_sub(th->obj[main->curr].hitpoint,
					  ((t_cyl *) th->obj[main->curr].data)->p1);
	proj = vec3_dp(th->obj[main->curr].dir_y, pos_hp);
	p = vec3_mult(th->obj[main->curr].dir_y, proj);
	c = vec3_norm(vec3_sub(th->obj[main->curr].hitpoint, p));
	th->obj[main->curr].uv.x = vec3_dp(c, th->obj[main->curr].dir_x);
	th->obj[main->curr].uv.y = proj / M_PI;
	if (th->obj[main->curr].uv.x < 0 && th->obj[main->curr].texture >= 9)
		th->obj[main->curr].uv.x = TEXT_S + th->obj[main->curr].uv.x;
	if (th->obj[main->curr].uv.y < 0 && th->obj[main->curr].texture >= 9)
		th->obj[main->curr].uv.y = TEXT_S + th->obj[main->curr].uv.y;
}