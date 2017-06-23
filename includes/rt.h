/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 13:33:53 by aradiuk           #+#    #+#             */
/*   Updated: 2017/06/07 13:33:54 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "libft.h"
//# include "parser.h"
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <time.h>


# define THREADS 4
# define WIDTH 1200
# define HEIGHT 720
# define ASPECT (double)WIDTH / (double)HEIGHT
# define FOV 45. * M_PI / 180.
# define AMBIENT 0.2
# define DIFFUSE 0.5
# define SPECULAR 0.2
# define OBJECTS 1
# define LIGHTS 1
# define MAXDEPTH 5
# define RAD M_PI / 180.

typedef struct	s_abs
{
	double a;
	double b;
	double c;
	double discr;
}				t_abs;

typedef	struct 	s_vec3
{
	double x;
	double y;
	double z;
}				t_vec3;

typedef	struct 	s_ray
{
	t_vec3	dir;
	t_vec3	pos;
	double	t_min;
	double	t_max;
}				t_ray;

typedef	struct 	s_matrix
{
	double m[4][4];
}				t_matrix;

typedef struct	s_matrices
{
	t_matrix	rot_x;
	t_matrix	rot_y;
	t_matrix	rot_z;
}				t_matrices;

typedef struct	s_scene
{
	int		wid;
	int		hei;
	int		objs;
	int 	lights;
}				t_scene;

typedef	struct 	s_sample
{
	int x;
	int	y;
}				t_sample;

typedef	struct 	s_inter
{
	t_vec3	pos;
	t_vec3	n;
	t_vec3	l;
	t_vec3	h;
}				t_inter;

typedef	struct	s_cam
{
	double	fov;
	t_ray	ray;
	t_vec3	rot;
}				t_cam;

typedef	struct	s_light
{
	t_ray	ray;
	t_vec3	color;
	int 	blocked;
}				t_light;

typedef enum 	e_mattype {
	LAMBERT,
	REFLECT_REFRACT,
	REFLECT
}				t_mattype;

typedef	struct 	s_material
{
	double	diff;
	double	spec;
	double	reflect;
	double 	refract; //index of refraction
	t_vec3	color;
}				t_material;

typedef struct	s_plane
{
	t_vec3		pos;
	t_vec3		normal;
	t_material	mat; //materials should be better in the general structures but easier to save them here for reading
}				t_plane;

typedef	struct 	s_sphere
{
	t_vec3		pos;
	double		rad;
	t_material	mat;
}				t_sphere;

typedef	struct		s_cyl
{
	t_vec3		p1;
	t_vec3		p2;
	t_vec3		axis;
	double		rad;
	int			cut;
	t_material	mat;
}					t_cyl;

typedef struct		s_cone
{
	t_vec3		p1;
	t_vec3		p2;
	t_vec3		axis;
	double		r1;
	double		r2;
	double		angle;
	int			cut;
	t_material	mat;
}					t_cone;

typedef struct 	s_torus
{
	t_vec3		pos;
	t_vec3		axis;
	double		r_min;
	double		r_mjr;
	t_material	mat;
}				t_torus;

typedef struct	s_flag
{
	int		cam;
	int		obj;
	int		lgh;
}				t_flag;

typedef	struct	s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*ipp;
	int				bpp;
	int				size_line;
	int				endian;
}				t_mlx;


typedef	struct 		s_obj
{
	char	*type;
	void	*data;
	t_material	mat;
	t_mattype mattype; //added here so that we do not need cast object
	int		(*intersect)(t_ray *r, void *data, double *t);
	t_vec3	n;
	t_vec3	hitpoint;
	t_vec3	(*normal)(void *data, t_vec3 hitpoint); //function to count normal
}					t_obj;

typedef struct		s_main
{
	t_obj		*obj;
	t_mlx		mlx;
	t_cam		cam;
	t_light		*light;
	t_flag		flag;
	t_scene		scene;
//	t_sample	sample;
//	int 		num_lights;
	int			light_i;
	int			obj_i;
	ssize_t		curr;
	//point where the current obj is hit
}					t_main;


typedef	struct 		s_thread
{
	t_main	main;
	t_obj	*obj;
	t_light *light;
	int		start;
	int 	end;
}					t_thread;

void	error(int param);
void	read_file(int fd, t_main *main);
void	default_values(t_main *main);
void	set_flag(char *str, t_main *main, int set_rem);
void	scene_line(int fd, t_main *main);
void	cam_light_obj_line(char *str, t_main *main, int cam_light_obj);
void	cam_params(char *str, t_main *main, int pos_rot_fov);
void	light_params(char *str, t_main *main, int pos_dir_col);
void	choose_object(char *str, t_main *main);
void	*mal_object(t_main *main);
void	free_arr_tmp(char **arr, char *tmp);

/*
** 		PLANE
*/
void	add_plane(char *str, t_main *main);
void	*default_plane(t_plane *plane);
void	fill_plane_data(char *str, t_plane *plane);
void	plane_params(char *str, t_plane *plane, int param);

/*
**		SPHERE
*/
void	add_sphere(char *str, t_main *main);
void	*default_sphere(t_sphere *sphere);
void	fill_sphere_data(char *str, t_sphere *sphere);
void	sphere_params(char *str, t_sphere *sphere, int param);

/*
** 		CYLINDER
*/
void	add_cylinder(char *str, t_main *main);
void	*default_cylinder(t_cyl *cyl);
void	fill_cylinder_data(char *str, t_cyl *cyl);
void	cyl_params(char *str, t_cyl *cyl, int param);

/*
** 		CONE
*/
void	add_cone(char *str, t_main *main);
void	*default_cone(t_cone *cone);
void	fill_cone_data(char *str, t_cone *cone);
void	cone_params(char *str, t_cone *cone, int param);

void	mlx_initialise(t_main *main);
void	*render(void *data);

int		cross_exit(void *a);
int 	key_hook(int keycode, t_main *main);

/*
** 		TORUS
*/

void	*default_torus(t_torus *torus);
void	torus_params(char *str, t_torus *torus, int param);
void	fill_torus_data(char *str, t_torus *torus);
void	add_torus(char *str, t_main *main);

/*
**		VECTORS
*/

t_vec3	vec3_create(double x, double y, double z);
t_vec3	vec3_norm(t_vec3 vector);
t_vec3	vec3_invert(t_vec3 vector);
t_vec3	vec3_add(t_vec3 vec1, t_vec3 vec2);
t_vec3	vec3_sub(t_vec3 vec1, t_vec3 vec2);
t_vec3	vec3_mult(t_vec3 vec, double multiplier);
t_vec3	vec3_fill_atoi(char **arr);
double	vec3_dp(t_vec3 vec1, t_vec3 vec2);
double	vec3_length(t_vec3 vec);
t_vec3 reflect_ray(const t_vec3 i, const t_vec3 n);


/*
** 		REMOVE THIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/
void	vec3_print(t_vec3 vec, char *str);
void	print_scene(t_main *main);
/*
 * whitted algorithm
 */
t_vec3	cast_ray(t_thread *th, t_main *main, t_ray ray, int depth);

/*
 * intersections.c
 */
int		solve_quadric(double discr, double *t, double b, double a);
int		intersect_plane(t_ray *r, void *p, double *t);
int		intersect_cone(t_ray *r, void *con, double *t);
int		intersect_cylind(t_ray *r, void *cyl, double *t);
int		inter_ray_sphere(t_ray *r, void *s, double *t);
int 	intersect_torus(t_ray *r, void *tor, double *t);

int		vec3_to_int(t_vec3 hitcolor);

int		trace(t_main *main, t_ray ray, double *t, ssize_t *curr, t_thread *th);
t_vec3	cylinder_norm(void * data, t_vec3 hitpoint);
t_vec3	cone_norm(void *data, t_vec3 hitpoint);
t_vec3	plane_norm(void *data, t_vec3 hitpoint);
t_vec3	sphere_norm(void *data, t_vec3 hitpoint);

t_mattype get_material_type(t_material mat);

#endif
