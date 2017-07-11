/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_and_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 14:11:32 by aradiuk           #+#    #+#             */
/*   Updated: 2017/06/08 14:11:33 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cam_params(char *str, t_main *main, int pos_rot_fov)
{
	char	*tmp;
	char	**arr;

	if (pos_rot_fov == 1)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</position>"));
		arr = ft_strsplit(tmp, ' ');
		main->cam.ray.pos = vec3_fill_atoi(arr);
		main->cam.ray.pos.x /= main->scene.wid;
		main->cam.ray.pos.y /= main->scene.hei;
		main->cam.start = main->cam.ray.pos;
		free_arr_tmp(arr, tmp);
	}
	else if (pos_rot_fov == 2)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</rotation>"));
		arr = ft_strsplit(tmp, ' ');
		main->cam.rot = vec3_fill_atoi(arr);
		free_arr_tmp(arr, tmp);
	}
}

void	light_params(char *str, t_main *main, int pos_dir_col)
{
	char	*tmp;
	char	**arr;
	int		color;

	if (pos_dir_col == 3)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</color>"));
		color = ft_atoi_base(tmp, "0123456789abcdef");
		main->light[main->light_i].color = vec3_create((color >> 16 & 0xFF) /
						255, (color >> 8 & 0xFF) / 255., (color & 0xFF) / 255.);
		free(tmp);
	}
	else if (pos_dir_col == 1 || pos_dir_col == 2)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen(pos_dir_col == 1 ?
											"</position>" : "</direction>"));
		arr = ft_strsplit(tmp, ' ');
		if (pos_dir_col == 1)
			main->light[main->light_i].ray.pos = vec3_fill_atoi(arr);
		else
			main->light[main->light_i].ray.dir = vec3_fill_atoi(arr);
		free_arr_tmp(arr, tmp);
	}
	else
		main->light[main->light_i].rad = ft_atoi(str);
}

void	choose_object(char *str, t_main *main)
{
	if (ft_strcmp(main->obj[main->obj_i].type, "plane") == 0)
		add_plane(str, main);
	if (ft_strcmp(main->obj[main->obj_i].type, "sphere") == 0)
		add_sphere(str, main);
	if (ft_strcmp(main->obj[main->obj_i].type, "cylinder") == 0)
		add_cylinder(str, main);
	if (ft_strcmp(main->obj[main->obj_i].type, "cone") == 0)
		add_cone(str, main);
	if (ft_strcmp(main->obj[main->obj_i].type, "torus") == 0)
		add_torus(str, main);
	if (ft_strcmp(main->obj[main->obj_i].type, "paraboloid") == 0)
		add_paraboloid(str, main);
}

void	*mal_object(t_main *main)
{
	if (ft_strcmp(main->obj[main->obj_i].type, "plane") == 0)
		return (default_plane((t_plane *)malloc(sizeof(t_plane))));
	if (ft_strcmp(main->obj[main->obj_i].type, "sphere") == 0)
		return (default_sphere((t_sphere *)malloc(sizeof(t_sphere))));
	if (ft_strcmp(main->obj[main->obj_i].type, "cylinder") == 0)
		return (default_cylinder((t_cyl *)malloc(sizeof(t_cyl))));
	if (ft_strcmp(main->obj[main->obj_i].type, "cone") == 0)
		return (default_cone((t_cone *)malloc(sizeof(t_cone))));
	if (ft_strcmp(main->obj[main->obj_i].type, "torus") == 0)
		return (default_torus((t_torus *)malloc(sizeof(t_torus))));
	if (ft_strcmp(main->obj[main->obj_i].type, "paraboloid") == 0)
		return (default_parab((t_parab *)malloc(sizeof(t_parab))));
	error(9);
	return (0);
}

void	cam_light_obj_line(char *str, t_main *main, int cam_light_obj)
{
	char	*t;

	while (ft_isspace(*str) == 1)
		str++;
	if (cam_light_obj == 1 && ft_strstr(str, "<position>"))
		cam_params(str + ft_strlen("<position>"), main, 1);
	if (cam_light_obj == 1 && ft_strstr(str, "<rotation>"))
		cam_params(str + ft_strlen("<rotation>"), main, 2);
	if (cam_light_obj == 2 && ft_strstr(str, "<position>"))
		light_params(str + ft_strlen("<position>"), main, 1);
	if (cam_light_obj == 2 && ft_strstr(str, "<direction>"))
		light_params(str + ft_strlen("<direction>"), main, 2);
	if (cam_light_obj == 2 && ft_strstr(str, "<color>"))
		light_params(str + ft_strlen("<color>"), main, 3);
	if (cam_light_obj == 2 && ft_strstr(str, "<radius>"))
		light_params(str + ft_strlen("<radius>"), main, 4);
	if (cam_light_obj == 3 && ft_strstr(str, "<object"))
	{
		t = ft_strstr(str, "type=") + 6;
		check_obj_type(t);
		main->obj[main->obj_i].type = ft_strsub(t, 0, ft_strchr(t, '\"') - t);
		main->obj[main->obj_i].data = mal_object(main);
	}
	else if (cam_light_obj == 3)
		choose_object(str, main);
}
