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

#include "../includes/rt.h"

void	cam_params(char *str, t_main *main, int pos_rot_fov)
{
	char 	*tmp;
	char	**arr;

	tmp = 0;
	if (pos_rot_fov == 1)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</position>"));
		arr = ft_strsplit(tmp, ',');
		main->cam.ray.pos.x = ft_atoi(arr[0]);
		main->cam.ray.pos.y = ft_atoi(arr[1]);
		main->cam.ray.pos.z = ft_atoi(arr[2]);
	}
	else if (pos_rot_fov == 2)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</rotation>"));
		arr = ft_strsplit(tmp, ',');
		main->cam.rot.x = ft_atoi(arr[0]);
		main->cam.rot.y = ft_atoi(arr[1]);
		main->cam.rot.z = ft_atoi(arr[2]);
	}
	else if (pos_rot_fov == 3)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</fov>"));
		main->cam.fov = ft_atoi(tmp);
	}
	if (pos_rot_fov == 1 || pos_rot_fov == 2)
	{
		free(arr[0]);
		free(arr[1]);
		free(arr[2]);
		free(arr);
	}
	free(tmp);
}

void	light_params(char *str, t_main *main, int pos_dir_col)
{
	char	*tmp;
	char	**arr;
	int		color;

	tmp = 0;
	if (pos_dir_col == 1)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</position>"));
		arr = ft_strsplit(tmp, ',');
		main->light[main->light_i].ray.pos.x = ft_atoi(arr[0]);
		main->light[main->light_i].ray.pos.y = ft_atoi(arr[1]);
		main->light[main->light_i].ray.pos.z = ft_atoi(arr[2]);
		free(arr[0]);
		free(arr[1]);
		free(arr[2]);
		free(arr);
	}
	else if (pos_dir_col == 2)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</direction>"));
		arr = ft_strsplit(tmp, ',');
		main->light[main->light_i].ray.dir.x = ft_atoi(arr[0]);
		main->light[main->light_i].ray.dir.y = ft_atoi(arr[1]);
		main->light[main->light_i].ray.dir.z = ft_atoi(arr[2]);
		free(arr[0]);
		free(arr[1]);
		free(arr[2]);
		free(arr);
	}
	else if (pos_dir_col == 3)
	{
		tmp = ft_strsub(str, 0, ft_strlen(str) - ft_strlen("</color>"));
		color = ft_atoi_base(tmp, "0123456789abcdef");
		main->light[main->light_i].color.x = color >> 16 & 0xFF;
		main->light[main->light_i].color.y = color >> 8 & 0xFF;
		main->light[main->light_i].color.z = color & 0xFF;
	}
	free(tmp);
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
	return (NULL);
}

void	cam_light_obj_line(char *str, t_main *main, int cam_light_obj)
{
	char	*tmp;

	while (ft_isspace(*str) == 1)
		str++;
	if (cam_light_obj == 1 && ft_strstr(str, "<position>"))
		cam_params(str + ft_strlen("<position>"), main, 1);
	if (cam_light_obj == 1 && ft_strstr(str, "<rotation>"))
		cam_params(str + ft_strlen("<rotation>"), main, 2);
	if (cam_light_obj == 1 && ft_strstr(str, "<fov>"))
		cam_params(str + ft_strlen("<fov>"), main, 3);
	if (cam_light_obj == 2 && ft_strstr(str, "<position>"))
		light_params(str + ft_strlen("<position>"), main, 1);
	if (cam_light_obj == 2 && ft_strstr(str, "<direction>"))
		light_params(str + ft_strlen("<direction>"), main, 2);
	if (cam_light_obj == 2 && ft_strstr(str, "<color>"))
		light_params(str + ft_strlen("<color>"), main, 3);
	if (cam_light_obj == 3 && ft_strstr(str, "<object"))
	{
		tmp = ft_strstr(str, "type=") + 6;
		main->obj[main->obj_i].type = ft_strsub(tmp, 0, ft_strchr(tmp, '\"') - tmp);
		main->obj[main->obj_i].data = mal_object(main);
	}
	else if (cam_light_obj == 3)
		choose_object(str, main);
}
