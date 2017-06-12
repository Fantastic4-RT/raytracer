//
// Created by Anastasiia Trepyton on 6/12/17.
//

#include "../includes/rt.h"

int vec3_to_int(t_vec3 hitcolor)
{
	return (((int)hitcolor.x << 16 | (int)hitcolor.y << 8 | (int)hitcolor.z));
}

double clamp(const double low, const double high, const double value)
{
	return fmax(low, fmin(high, value));
}

/*
 * Compute reflection direction
 */
t_vec3 reflect_ray(const t_vec3 i, const t_vec3 n)
{
	return (vec3_sub(i, vec3_mult(n, 2 * (vec3_dp(i, n)))));
}

/*
 * Compute refraction direction
 */

t_vec3 refract_ray(const t_vec3 i, const t_vec3 n, const double irefract)
{
	double cosi = clamp(-1, 1, vec3_dp(i, n));
	double etai = 1;
	double etat = irefract;
	t_vec3 norm = n;

	if (cosi < 0)
		cosi = -cosi;
	else
	{
		ft_swap(&etai, &etat);
		norm = vec3_invert(n);
	}
	double eta = etai / etat;
	double k = 1 - eta * eta * (1 - cosi * cosi);
	return (k < 0 ? 0 : vec3_add(vec3_mult(i, eta), vec3_mult(norm, (eta * cosi - sqrt(k)))));
}

/*
 * Compute Fresnel equation
 */

void	frensel(const t_vec3 i, const t_vec3 n, const double irefract, double *amount)
{
	double cosi = clamp(-1, 1, vec3_dp(i, n));
	double etai = 1;
	double etat = irefract;
	if (cosi > 0)
		ft_swap(&etai, &etat);

	double sint = etai / etat * sqrt(fmax(0.0, 1 - cosi * cosi));
	if (sint >= 1)
		*amount = 1;
	else
	{
		double cost = sqrt(fmax(0.0, 1 - sint * sint));
		cosi = fabs(cosi);
		double rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		double rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		*amount = (rs * rs + rp * rp) / 2;
	}
}
/*
 * compute color for different materials
 */
t_vec3 reflection_and_refraction()
{

}

t_vec3 reflection()
{

}

t_vec3 diffuse()
{

}

/*
 * trace light
 * Returns true if the ray intersects an object, false otherwise.
 */
int trace(t_main *main, double *t, t_vec2 *uv, ssize_t *curr)
{
	ssize_t i;
	i = 0;
	while (i < main->obj_i) //nb of objects?
	{
		double t1 = 1000000;
		t_vec2 uv1;
		if (/*object intersected*/ && t1 < *t) //intersection functions
		{
			*curr = i;
			*t = t1;
			*uv = uv1; //ЗАЧЕМ нам u and v barycentric coordinates of the intersected point? для текстур?
		}
	}
	return (*curr == -1 ? 0 : 1);
}
/*
 * Cast rays recursive algorithm
 */
int cast_ray(t_main *main, int depth)
{
	if (depth > MAXDEPTH)
		return (0); // returns background color
	t_vec3 hitcolor;
	hitcolor = vec3_create(0, 0, 0);
	double t;
	t = 1000000;
	t_vec2 uv; //uv coordinates of intersection point
	ssize_t curr = -1;
	if (trace(main, &t, &uv, &curr))
	{
		t_vec3 hitpoint = vec3_add(main->cam.ray.pos, vec3_mult(main->cam.ray.dir, t));
		t_vec3 norm;
		t_vec2 st;
		//get_surface_properties(hitpoint, e->cam.ray.dir, uv, &norm, &st); //(*main) different for each obj
		t_vec3 tmp;
		/*
		 * three types of material
		 */
		if ("object.material is reflective && refractive") //transtarent
			hitcolor = reflection_and_refraction();
		else if ("object.material is reflective") //mirror-like
			hitcolor = reflection();
		else //diffuse
			hitcolor = diffuse();
	}
	return(vec3_to_int(hitcolor));
}