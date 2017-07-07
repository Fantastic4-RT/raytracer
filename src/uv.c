
#include "rt.h"

void	sphere_uv(t_thread *th, t_main *main)
{
	double phi;
	double theta;

	phi = acos(-vec3_dp(th->obj[main->curr].dir_y, th->obj[main->curr].n));
	th->obj[main->curr].uv.y = phi / M_PI;
	theta = (acos(vec3_dp(th->obj[main->curr].n, th->obj[main->curr].dir_x)) / sin(phi)) / (2 * M_PI);
	if (vec3_dp(vec3_cross(th->obj[main->curr].dir_y, th->obj[main->curr].dir_x), th->obj[main->curr].n) > 0)
		th->obj[main->curr].uv.x = theta;
	else
		th->obj[main->curr].uv.x = 1 - theta;
}

void	plane_uv(t_thread *th, t_main *main)
{

}
//void	cone_uv(t_thread *th, t_main *main);
//void	cylinder_uv(t_thread *th, t_main *main);