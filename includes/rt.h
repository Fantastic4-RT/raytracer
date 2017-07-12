/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrepyto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 16:01:37 by atrepyto          #+#    #+#             */
/*   Updated: 2017/07/09 16:01:41 by atrepyto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "libft.h"
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
# define FOV 45.* M_PI / 180.
# define AMBIENT 0.2
# define DIFFUSE 0.5
# define SPEC 0.2
# define OBJECTS 1
# define LIGHTS 1
# define MAXDEPTH 5
# define RAD M_PI / 180.
# define ROT_ANGLE 15* RAD
# define OBJ_ROT 2
# define TEXT_S 256
# define MAX_DEGREE 4

typedef struct		s_abs
{
	double		a;
	double		b;
	double		c;
	double		discr;
}					t_abs;

typedef struct		s_cube
{
	double	q;
	double	p;
	double	t;
	double	u;
	double	s_real;
	double	s_abs;
	double	s_phase;
	double	u_abs;
	double	u_phase;
	double	u_real;
}					t_cube;

typedef struct		s_quad
{
	double	helper_cubic[4];
	double	helper_results[3];
	double	quadratic_factor[3];
	double	p;
	double	e;
	double	d;
	double	c;
	int		num_results;
	int		num_quad_results;
	double	quadratic[3];
	double	quadratic_results[2];
	double	s;
}					t_quad;

typedef struct		s_polynome4
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	e;
	double	x[4];
	t_cube	d_cube;
	t_quad	d_quad;
	double	poly[5];
	double	normalized_poly[MAX_DEGREE + 1];
	double	rev_poly[MAX_DEGREE + 1];
}					t_polynome4;

typedef	struct		s_vec3
{
	double		x;
	double		y;
	double		z;
}					t_vec3;

typedef	struct		s_ray
{
	t_vec3		dir;
	t_vec3		pos;
}					t_ray;

typedef	struct		s_matrix
{
	double		m[4][4];
}					t_matrix;

typedef struct		s_matrices
{
	t_matrix	rot_x_cam;
	t_matrix	rot_y_cam;
	t_matrix	rot_z_cam;
	t_matrix	rot_cam;
	t_matrix	rot_x_dir;
	t_matrix	rot_y_dir;
	t_matrix	rot_z_dir;
	t_matrix	rot_dir;
	t_vec3		cam_angle;
	t_vec3		dir_angle;
}					t_matrices;

typedef struct		s_scene
{
	int		wid;
	int		hei;
	int		objs;
	int		lights;
	int		a_a;
	int		m_b;
	int		sepia;
	int		grey;
	int		eff;
	double	amb;
}					t_scene;

typedef	struct		s_cam
{
	t_ray		ray;
	t_vec3		start;
	t_vec3		rot;
	double		fov;
}					t_cam;

typedef	struct		s_light
{
	t_ray		ray;
	t_vec3		color;
	double		rad;
}					t_light;

typedef enum		e_mattype
{
	LAMBERT,
	REFLECT_REFRACT,
	REFLECT
}					t_mattype;

typedef	struct		s_material
{
	double		diff;
	double		spec;
	double		reflect;
	double		refract;
	double		transp;
	t_vec3		color;
}					t_material;

typedef struct		s_plane
{
	t_vec3		pos;
	t_vec3		normal;
	t_vec3		p2;
	t_vec3		p3;
	t_vec3		p4;
	double		rad;
	int			cut;
	t_material	mat;
}					t_plane;

typedef	struct		s_sphere
{
	t_vec3		pos;
	t_vec3		p1;
	double		tt[2];
	double		rad;
	int			hit_obj;
	int			cut;
	t_material	mat;
}					t_sphere;

typedef	struct		s_cyl
{
	t_vec3		p1;
	t_vec3		p2;
	t_vec3		axis;
	double		rad;
	int			cut;
	double		t_low_cap;
	double		t_top_cap;
	double		t_final;
	int			cyl_hit;
	t_material	mat;
}					t_cyl;

typedef struct		s_cone
{
	t_vec3		p1;
	t_vec3		p2;
	t_vec3		apex;
	t_vec3		axis;
	double		r1;
	double		r2;
	double		angle;
	int			cut;
	t_material	mat;
	int			cone_hit;
}					t_cone;

typedef struct		s_inter_tor
{
	double		tmp_u;
	double		tmp_v;
	double		tmp_a;
	double		tmp_b;
	double		tmp_c;
	double		tmp_d;
}					t_inter_tor;

typedef struct		s_norm_tor
{
	t_vec3		a;
	double		y;
	t_vec3		b;
	t_vec3		d;
	double		c;
	double		m;
	t_vec3		k;
	t_vec3		x;
}					t_norm_tor;

typedef struct		s_torus
{
	t_vec3		pos;
	t_vec3		axis;
	double		r_min;
	double		r_mjr;
	t_material	mat;
	t_inter_tor	intersect;
	t_norm_tor	norm;
}					t_torus;

typedef struct		s_parab
{
	t_vec3		pos;
	t_vec3		axis;
	double		k;
	t_material	mat;
}					t_parab;

typedef struct		s_flag
{
	int			cam;
	int			obj;
	int			lgh;
}					t_flag;

typedef struct		s_menu
{
	void		*menu_win;
	void		*main_menu;
	void		*side_arr;
	void		*vert_arr;
	int			w;
	int			h;
}					t_menu;

typedef	struct		s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*ipp;
	int			bpp;
	int			size_line;
	int			endian;
	t_menu		menu;
}					t_mlx;

typedef	struct		s_obj
{
	char		*type;
	void		*data;
	t_material	mat;
	t_mattype	mattype;
	int			(*intersect)(t_ray r, void *data, double *t);
	t_vec3		n;
	t_vec3		hitpoint;
	t_vec3		tmp_color;
	t_vec3		(*normal)(void *data, t_vec3 hitpoint);
	int			texture;
	t_vec3		uv;
	t_vec3		dir_x;
	t_vec3		dir_y;
}					t_obj;

typedef struct		s_pmode
{
	int			obj_mode;
	int			move_mode;
	int			obj_index;
	int			rot_obj_mode;
	int			text_mode;
	int			color_mode;
	int			cam_mode;
	int			dir_mode;
	int			rot_cam_mode;
	int			cam_pos_mode;
	int			off;
	int			start;
	int			loaded;
	char		channel;
	t_vec3		count;
}					t_pmode;

typedef struct		s_text
{
	double		text_arr[TEXT_S][TEXT_S];
	int			zoom;
}					t_text;

typedef struct		s_img
{
	void		*img;
	char		*data;
	int			h;
	int			w;
	int			endian;
	int			sl;
	int			bpp;
}					t_img;

typedef struct		s_main
{
	t_obj			*obj;
	t_mlx			mlx;
	t_cam			cam;
	t_light			*light;
	t_flag			flag;
	t_scene			scene;
	t_pmode			mode;
	t_text			textures[1];
	t_img			img[5];
	int				light_i;
	int				obj_i;
	ssize_t			curr;
	t_vec3			diff_col;
	t_matrices		mxs;
	unsigned int	pic;
	char			*filename;
	int				toon;
}					t_main;

typedef	struct		s_thread
{
	t_main		main;
	t_obj		*obj;
	t_light		*light;
	int			start;
	int			end;
}					t_thread;

/*
** algo_help.c
*/
int					vec3_to_int(t_vec3 hitcolor);
double				clamp(const double low, const double high,
							const double value);
t_vec3				reflect_ray(const t_vec3 i, const t_vec3 n);
t_vec3				refract_ray(const t_vec3 i, const t_vec3 n,
							const double irefract);
void				fresnel(const t_vec3 i,
					const t_vec3 n, const double ir, double *am);
/*
** antialiasing.c
*/
t_vec3				vec3_comp_dp(t_vec3 v1, t_vec3 v2);
int					trace(t_ray ray, double *t, ssize_t *curr, t_thread *th);
void				ft_aa(t_thread *th, double dist, int x, int y);
int					ft_col_av(t_thread *th, t_vec3 *col);
t_vec3				ft_tracer_aa(t_thread *th, t_vec3 p);
/*
** cam_and_light.c
*/
void				cam_params(char *str, t_main *main, int pos_rot_fov);
void				light_params(char *str, t_main *main, int pos_dir_col);
void				choose_object(char *str, t_main *main);
void				*mal_object(t_main *main);
void				cam_light_obj_line(char *str,
							t_main *main, int cam_light_obj);
/*
**  camera_mode.c
*/
void				switch_cam_mode(int keycode, t_main *main);
void				camera_position(int keycode, t_main *main);
void				camera_direction(int keycode, t_main *main);
void				camera_rotation(int keycode, t_main *main);
void				last_check(char *str, t_main *main);
/*
** cone.c
*/
void				*default_cone(t_cone *cone);
void				cone_params_2(char *str, t_cone *cone, int param);
void				cone_params(char *str, t_cone *cone, int param);
void				fill_cone_data(char *str, t_cone *cone);
void				add_cone(char *str, t_main *main);
/*
** cut_intersections.c
*/
int					inter_ray_sphere_cut(t_ray r, void *sphere, double *t);
int					intersect_cylind_cut(t_ray r, void *cyl, double *t);
int					intersect_parab(t_ray r, void *par, double *t);
void				z_obj_rot(int keycode, t_main *main);
/*
** cut_normals.c
*/
t_vec3				sphere_norm_cut(void *data, t_vec3 hitpoint);
t_vec3				cone_norm_cut(void *data, t_vec3 hitpoint);
t_vec3				cylinder_norm_cut(void *data, t_vec3 hitpoint);
/*
** cut_plane.c
*/
int					intersect_triangle(t_ray r, void *p, double *t);
int					intersect_elips(t_ray r, void *p, double *t);
int					intersect_mesh(t_ray r, void *p, double *t);
/*
** cylinder.c
*/
void				*default_cylinder(t_cyl *cyl);
void				cyl_params_2(char *str, t_cyl *cyl, int param);
void				cyl_params(char *str, t_cyl *cyl, int param);
void				fill_cylinder_data(char *str, t_cyl *cyl);
void				add_cylinder(char *str, t_main *main);
/*
** envinronment.c
*/
void				alias_mode(int keycode, t_main *main);
void				init_images(t_main *main);
t_mattype			get_material_type(t_material mat);
void				print_status(t_main *main);
/*
** finit_cone.c
*/
void				check_inters(t_ray r, t_cone *cone, double tt[], int tmp[]);
void				check_tt(double *t, double tt[], int tmp[]);
int					intersect_cone_cut(t_ray r, void *s, double *t);
t_vec3				ft_sepia_grey(t_thread *th, t_vec3 col);
/*
** finit_cyl.c
*/
double				ft_check_min(double t1, double t2);
double				ft_find_caps(t_cyl *cyl, t_ray r, double t, t_vec3 p);
double				intersect_plane1(t_cyl *cyl, t_ray r, t_vec3 pos, double t);
double				ft_check_between(t_cyl *cyl, t_vec3 pos,
							t_vec3 dir, double t);
void				ft_caps(t_cyl *cyl, t_ray r, double *t, double *t_final);
int					solve_quadric_cut(t_abs solve, double *t_final,
							t_cyl *cyl, t_ray r);
/*
** hooks.c
*/
int					cross_exit(void *a);
void				cam_hook(t_main *main);
void				change_mode(int keycode, t_main *main);
int					key_hook(int keycode, t_main *main);
void				output(char *str, int nb);
/*
**  initialise.c
*/
void				ml_d(t_obj *obj1, t_obj *obj2, char *str);
void				pthreading(t_main *main);
void				outputfile(t_main *main);
void				image(t_main *main);
void				mlx_initialise(t_main *main);
/*
** intersections.c
*/
int					inter_ray_sphere(t_ray r, void *s, double *t);
int					intersect_cylind(t_ray r, void *cyl, double *t);
int					intersect_cone(t_ray r, void *con, double *t);
int					intersect_plane(t_ray r, void *p, double *t);
int					solve_quadric(double discr, double *t, double b, double a);
/*
** main.c
*/
int					expose(t_main *main);
void				check_obj_type(char *t);
void				error(int param);
void				default_values(t_main *main);
int					main(int argc, char **argv);
/*
** mapping.c
*/
void				find_pixel_color(t_thread *th, t_main *main);
void				find_img_cd(t_thread *th, t_main *main);
void				find_disturb_cd2(t_thread *th, t_main *main, t_vec3 p);
void				find_disturb_cd(t_thread *th, t_main *main, t_vec3 p);
void				get_uv_coordinates(t_thread *th, t_main *main);
/*
** matrix_func.c
*/
t_matrix			m_mult(t_matrix m1, t_matrix m2);
t_matrix			x_rot(double angle);
t_matrix			y_rot(double angle);
t_matrix			z_rot(double angle);
t_matrix			tr(t_vec3 pos);

/*
** normals.c
*/
t_vec3				sphere_norm(void *data, t_vec3 hitpoint);
t_vec3				plane_norm(void *data, t_vec3 hitpoint);
t_vec3				cone_norm(void *data, t_vec3 hitpoint);
t_vec3				cylinder_norm(void *data, t_vec3 hitpoint);
t_vec3				parab_norm(void *data, t_vec3 hitpoint);
/*
** obj_rotations_x.c
*/
void				x_object_rotation1(int keycode, t_main *main);
void				x_object_rotation2(int keycode, t_main *main);
void				x_object_rotation3(int keycode, t_main *main);
void				x_object_rotation4(int keycode, t_main *main);
void				x_dirextions_rot(int keycode, t_main *main);
/*
** obj_rotations_y.c
*/
void				y_object_rotation1(int keycode, t_main *main);
void				y_object_rotation2(int keycode, t_main *main);
void				y_object_rotation3(int keycode, t_main *main);
void				y_object_rotation4(int keycode, t_main *main);
void				y_dirextions_rot(int keycode, t_main *main);
/*
** obj_rotations_z.c
*/
void				z_object_rotation1(int keycode, t_main *main);
void				z_object_rotation2(int keycode, t_main *main);
void				z_object_rotation3(int keycode, t_main *main);
void				z_object_rotation4(int keycode, t_main *main);
void				z_dirextions_rot(int keycode, t_main *main);
/*
** obj_translations_x.c
*/
void				x_object_translation1(int keycode, t_main *main);
void				x_object_translation2(int keycode, t_main *main);
void				x_object_translation3(int keycode, t_main *main);
void				x_object_translation4(int keycode, t_main *main);
/*
** obj_translations_y.c
*/
void				y_object_translation1(int keycode, t_main *main);
void				y_object_translation2(int keycode, t_main *main);
void				y_object_translation3(int keycode, t_main *main);
void				y_object_translation4(int keycode, t_main *main);
void				y_object_rotation5(int keycode, t_main *main);
/*
** obj_translations_z.c
*/
void				z_object_translation1(int keycode, t_main *main);
void				z_object_translation2(int keycode, t_main *main);
void				z_object_translation3(int keycode, t_main *main);
void				z_object_translation4(int keycode, t_main *main);
void				z_object_rotation5(int keycode, t_main *main);
/*
** object_functions.c
*/
void				image_texture(int keycode, t_main *main);
void				rotate_objects(int keycode, t_main *main);
int					channels_change(int keycode, t_main *main);
void				change_color(int keycode, t_main *main);
void				move_objects(int keycode, t_main *main);
/*
**  object_mode.c
*/
void				color_mode(int keycode, t_main *main);
void				texture_mode(int keycode, t_main *main);
void				move_mode(int keycode, t_main *main);
void				rotation_mode(int keycode, t_main *main);
void				switch_obj_mode(int keycode, t_main *main);
/*
**  paraboloid.c
*/
void				*default_parab(t_parab *parab);
void				parab_params_2(char *str, t_parab *parab, int param);
void				parab_params(char *str, t_parab *parab, int param);
void				fill_parab_data(char *str, t_parab *parab);
void				add_paraboloid(char *str, t_main *main);
/*
**  plane.c
*/
void				add_plane(char *str, t_main *main);
void				fill_plane_data(char *str, t_plane *plane);
void				plane_params(char *str, t_plane *plane, int param);
void				plane_params_2(char *str, t_plane *plane, int param);
void				*default_plane(t_plane *plane);
/*
**  read_help.c
*/
void				free_arr_tmp(char **arr, char *tmp);
t_vec3				vec3_fill_atoi(char **arr);
void				scene_line(int fd, t_main *main);
void				set_flag(char *str, t_main *main, int set_rem);
void				read_file(int fd, t_main *main);
/*
**  render.c
*/
void				free_thread(t_thread *data);
void				one_ray(t_thread *th, double dist, int x, int y);
void				*render(void *data);
t_vec3				m_apply(t_matrix matrix, t_vec3 vec);
void				matrices(t_main *main);
/*
** sphere.c
*/
void				add_sphere(char *str, t_main *main);
void				fill_sphere_data(char *str, t_sphere *sphere);
void				sphere_params(char *str, t_sphere *sphere, int param);
void				sphere_params_2(char *str, t_sphere *sphere, int param);
void				*default_sphere(t_sphere *sphere);
/*
** texture_gen.c
*/
t_vec3				int_to_vec3(int color);
void				perlin_noise(t_main *main, float zoom);
void				generate_textures(t_main *main);
void				change_texture(int keycode, t_main *main);
void				toon_effect(t_vec3	df_sp[], t_vec3	*hitcol, t_main *main);
/*
** textures.c
*/
double				marble(t_vec3 p, t_main *main);
double				wood(t_vec3 p, t_main *main);
double				sin_stripes(t_vec3 p, t_thread *th, int w);
double				turbulence(t_vec3 p, t_main *main, double size);
double				smooth_noise(t_vec3 p, t_main *main);
/*
** uv.c
*/
void				sphere_uv(t_thread *th, t_main *main);
void				plane_uv(t_thread *th, t_main *main);
void				cone_uv(t_thread *th, t_main *main);
void				cylinder_uv(t_thread *th, t_main *main);
t_vec3				vec3_zero();
/*
** vector_operations.c
*/
t_vec3				vec3_create(double x, double y, double z);
t_vec3				vec3_norm(t_vec3 vector);
t_vec3				vec3_invert(t_vec3 vector);
double				vec3_dp(t_vec3 vec1, t_vec3 vec2);
int					vec3_eq(t_vec3 vec1, t_vec3 vec2);
/*
** vector_operations_2.c
*/
t_vec3				vec3_add(t_vec3 vec1, t_vec3 vec2);
t_vec3				vec3_sub(t_vec3 vec1, t_vec3 vec2);
t_vec3				vec3_mult(t_vec3 vec, double multiplier);
double				vec3_length(t_vec3 vec);
t_vec3				vec3_cross(t_vec3 vec1, t_vec3 vec2);
/*
**  whitted_algorithm.c
*/
t_vec3				reflect_and_refract
					(t_vec3 hitcol, t_ray *ray, int depth, t_thread *th);
t_vec3				reflection(t_vec3 hitcol, t_ray ray,
							int depth, t_thread *th);
void				phong_col(t_ray *lray, t_vec3 df_sp[],
							t_thread *th, t_ray *ray);
t_vec3				diffuse(t_vec3 hitcolor, t_ray *ray, t_main *main,
							t_thread *th);
t_vec3				cast_ray(t_thread *th, t_main *main, t_ray ray, int depth);
/*
** 	motion_blur.c
*/
t_vec3				ft_mb(t_thread *th);
void				ft_check_type(t_thread *th);
void				ft_check_type_minus(t_thread *th);
t_vec3				ft_col_av1(t_vec3 *col);
/*
** 	torus.c
*/
void				*default_torus(t_torus *torus);
void				torus_params(char *str, t_torus *torus, int param);
void				fill_torus_data(char *str, t_torus *torus);
void				add_torus(char *str, t_main *main);
/*
** 	torus_intrsect_normals.c
*/
double				min_res(t_polynome4 *solve);
int					solve_polynome_4(double *t, t_polynome4 *solve);
t_vec3				torus_norm(void *data, t_vec3 hitpoint);
int					intersect_torus(t_ray r, void *tor, double *t);
/*
** 	polynome_4_resolve_1.c
*/
int					solve_real_poly_1(int degree, const double *poly,
						double *results, t_polynome4 *solve);
void				solve_real_poly_2(int degree, const double *poly,
						t_polynome4 *solve, double a);
double				stableness_score(double a, double b);
int					solve_normalized_poly(int degree, const double *poly,
						double *results, t_polynome4 *solve);
void				calc_shifted_coefs(double shift, int degree,
								const double *src, double *dst);
/*
** 	polynome_4_resolve_2.c
*/
void				calc_binomials(int num_binoms, int stride, double *dst);
void				calc_powers(double x, int max_power, double *dst);
int					solve_depressed_poly(int degree, const double *poly,
										double *results, t_polynome4 *solve);
double				cubic_root(double x);
int					solve_depressed_quadratic(const double *poly,
										double *results);
/*
** 	polynome_4_resolve_3.c
*/
int					solve_depressed_quartic_1(const double *poly,
										double *results, t_polynome4 *solve);
void				solve_depressed_quartic_2(t_polynome4 *solve,
										double *results);
void				solve_depressed_quartic_3(t_polynome4 *solve,
										double *results);
int					solve_depressed_cubic_1(const double *poly, double *results,
							t_polynome4 *solve);
void				solve_depressed_cubic_2(t_polynome4 *solve);

#endif
