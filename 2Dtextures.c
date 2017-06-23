//
// Created by Anastasiia Trepyton on 6/10/17.
//

#include "rt.h"

void texture2d(t_env *e, int curr)
{
	double alpha;
	double beta;

	alpha = acos((e->scene.point.z - e->scene.obs[curr].pos.z) /  e->scene.obs[curr].radius);
	beta = atan2(e->scene.point.y -  e->scene.obs[curr].pos.y,
				 e->scene.point.x - e->scene.obs[curr].pos.x);
	double u;
	double v;

//	u = fabs(e->scene.n.x / 2 + 0.5) * e->scene.img[0].w;
//	v = fabs(e->scene.n.y / 2 + 0.5) * e->scene.img[0].h;

	u = beta / 2 * M_PI;
	v = (M_PI - alpha) / M_PI;
	int i = (int)(u * e->scene.img[0].bpp / 8 + v * e->scene.img[0].sl);
	e->scene.obs[curr].color.x = e->scene.img[0].data[i];
	e->scene.obs[curr].color.y = e->scene.img[0].data[++i];
	e->scene.obs[curr].color.z = e->scene.img[0].data[++i];
}