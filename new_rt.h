//
// Created by Anastasiia Trepyton on 7/3/17.
//

#ifndef RT_H
# define RT_H
# include "libft.h"
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <fcntl.h>

# define THREADS 4
# define WIDTH 1200
# define HEIGHT 720
# define ASPECT (double)WIDTH / (double)HEIGHT
# define FOV 45. * M_PI / 180.
# define AMBIENT 0.2
# define SPECULAR 0.2
# define OBJECTS 1
# define LIGHTS 1
# define MAXDEPTH 5
# define RAD M_PI / 180.
# define ROT_ANGLE 15 * RAD
# define TEXT_SIZE 256

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
}				t_matrices;

typedef struct	s_scene
{
	int		wid;
	int		hei;
	int		objs;
	int 	lights;
	int     a_a;
	double	amb;
}				t_scene;

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
	t_vec3	start;
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
	double 	refract;
	double	transp;
	t_vec3	color;
}				t_material;

typedef struct	s_plane
{
	t_vec3		pos;
	t_vec3		normal;
	t_vec3		p2;
	t_vec3		p3;
	t_vec3		p4;
	double		rad;
	int			cut;
	t_material	mat;
}				t_plane;



typedef	struct 	s_sphere
{
	t_vec3		pos;
	t_vec3		p1;
	double		tt[2];
	double		rad;
	int			hit_obj;
	int			cut;
	t_material	mat;
}				t_sphere;

typedef	struct		s_cyl
{
	t_vec3		p1;
	t_vec3		p2;
	t_vec3		axis;
	double		rad;
	int			cut;
	double      t_low_cap;
	double      t_top_cap;
	double      t_final;
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
	int cone_hit; // 1 = cone, 2 = low, 3 = top
}					t_cone;

typedef struct		s_parab
{
	t_vec3		pos;
	t_vec3		axis;
	double		k;
	t_material	mat;
}					t_parab;

typedef struct	s_flag
{
	int		cam;
	int		obj;
	int		lgh;
}				t_flag;

typedef struct s_menu
{
	void	*menu_win;
	void	*main_menu;
	int		w;
	int 	h;
	void	*side_arr;
	void 	*vert_arr;
}				t_menu;

typedef	struct	s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*ipp;
	int				bpp;
	int				size_line;
	int				endian;
	t_menu			menu;
}				t_mlx;


typedef	struct 		s_obj
{
	char	*type;
	void	*data;
	t_material	mat;
	t_mattype mattype;
	int		(*intersect)(t_ray r, void *data, double *t);
	t_vec3	n;
	t_vec3	hitpoint;
	t_vec3	tmp_color;
	t_vec3	(*normal)(void *data, t_vec3 hitpoint);
	int 	texture;
}					t_obj;

typedef struct	s_pmode
{
	int obj_mode;
	int move_mode;
	int obj_index;
	int rot_obj_mode;
	int text_mode;
	int text_index;
	int color_mode;
	char channel;

	int cam_mode;
	int dir_mode;
	int rot_cam_mode;
	int cam_pos_mode;

	int off;
	int start;
	int loaded;

}				t_pmode;

typedef struct s_text
{
	double text_arr[TEXT_SIZE][TEXT_SIZE][TEXT_SIZE];
	int zoom;
}				t_text;

typedef struct		s_main
{
	t_obj		*obj;
	t_mlx		mlx;
	t_cam		cam;
	t_light		*light;
	t_flag		flag;
	t_scene		scene;
	t_pmode		mode;
	t_text 		*textures;
	int			light_i;
	int			obj_i;
	ssize_t		curr;
	t_vec3		diff_col;
	t_matrices	mxs;
	unsigned  int pic;
	char 		*filename;
}					t_main;


typedef	struct 		s_thread
{
	t_main	main;
	t_obj	*obj;
	t_light *light;
	int		start;
	int 	end;
}					t_thread;

/*
 * object_functions.c
 */
void	rotate_objects(int keycode, t_main *main);
void	change_texture(int keycode, t_main *main);
int		channels_change(int keycode, t_main *main);
void	change_color(int keycode, t_main *main);
void	move_objects(int keycode, t_main *main);
/*
 * obj_rotations_x.c
 */
void	x_object_rotation1(int keycode, t_main *main);
void	x_object_rotation2(int keycode, t_main *main);
void	x_object_rotation3(int keycode, t_main *main);

/*
 * obj_rotations_y.c
 */
void	y_object_rotation1(int keycode, t_main *main);
void	y_object_rotation2(int keycode, t_main *main);
void	y_object_rotation3(int keycode, t_main *main);

/*
 * obj_rotations_z.c
 */
void	z_object_rotation1(int keycode, t_main *main);
void	z_object_rotation2(int keycode, t_main *main);
void	z_object_rotation3(int keycode, t_main *main);
/*
 * obj_translations_x.c
 */
void	x_object_translation1(int keycode, t_main *main);
void	x_object_translation2(int keycode, t_main *main);
void	x_object_translation3(int keycode, t_main *main);
/*
 * obj_translations_y.c
 */
void	y_object_translation1(int keycode, t_main *main);
void	y_object_translation2(int keycode, t_main *main);
void	y_object_translation3(int keycode, t_main *main);
/*
 * obj_translations_z.c
 */
void	z_object_translation1(int keycode, t_main *main);
void	z_object_translation2(int keycode, t_main *main);
void	z_object_translation3(int keycode, t_main *main);
#endif